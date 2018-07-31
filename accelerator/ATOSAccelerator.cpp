#include "ATOSAccelerator.hpp"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TSocket.h>

namespace xacc {
namespace quantum {

std::shared_ptr<AcceleratorBuffer> ATOSAccelerator::createBuffer(
		const std::string& varId) {
	return createBuffer(varId, 100);
}

std::shared_ptr<AcceleratorBuffer> ATOSAccelerator::createBuffer(
		const std::string& varId, const int size) {
	if (!isValidBufferSize(size)) {
		xacc::error("ATOS - Invalid buffer size.");
	}
	auto buffer = std::make_shared<AcceleratorBuffer>(varId, size);
	storeBuffer(varId, buffer);
	return buffer;
}

bool ATOSAccelerator::isValidBufferSize(const int NBits) {
	return NBits <= 1000;
}

std::vector<std::shared_ptr<AcceleratorBuffer>> ATOSAccelerator::execute(
		std::shared_ptr<AcceleratorBuffer> buffer,
		const std::vector<std::shared_ptr<Function>> functions) {
	int counter = 0;
	std::vector<std::shared_ptr<AcceleratorBuffer>> tmpBuffers;
	for (auto f : functions) {
		auto tmpBuffer = createBuffer(
				buffer->name() + std::to_string(counter), buffer->size());
		execute(tmpBuffer, f);
		tmpBuffers.push_back(tmpBuffer);
		counter++;
	}

	return tmpBuffers;
}

void ATOSAccelerator::execute(std::shared_ptr<AcceleratorBuffer> buffer,
		const std::shared_ptr<xacc::Function> kernel) {

	//if (!std::dynamic_pointer_cast<AcceleratorBuffer>(buffer)) {
	//	xacc::error("Invalid AcceleratorBuffer, must be an ATOSBuffer.");
	//}

	//std::string visitorType = "atos";
	//if (xacc::optionExists("atos-visitor")) {
	//	visitorType = xacc::getOption("atos-visitor");
	//}

	//visitor = xacc::getService<ATOSVisitor>(visitorType);
	//visitor->initialize(buffer);

	auto visitor = std::make_shared<ATOSVisitor>();
	datamodel::Circuit circuit;

	InstructionIterator it(kernel);
	while (it.hasNext()) {
		auto nextInst = it.next();
		if (nextInst->isEnabled()) {
			nextInst->accept(visitor);
		}
	}
	circuit = visitor->getCircuit();
	std::vector<qpu::Result> results;
	task::Task task;
	task.__set_circuit(circuit);
	qpu::exec_options options;
	std::vector<int> qbits(circuit.nbqbits);

	for (int i = 0; i < circuit.nbqbits; i++) {
          qbits[i] = i;
        }

        options.__set_qbits(qbits);

	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 21290));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	qpu::FrontendClient qpu_client(protocol);
        transport->open();

	//qpu::FrontendClient qpu = qpu_client("localhost", 21290);
	
	qpu_client.Execute(results, task, options);

	for ( auto result : results) {
          std::cout << "####BEGIN####\n" << result << std::endl;
          std::string state = result.state;
          std::cout << "binary state [ qbit_"<< state.size() * 8 << ", qbit_" << 0 << "]: " << std::endl;
	  buffer->appendMeasurement(state);
          for (std::size_t i = 0; i < state.size(); ++i)
          {
            std:: cout << std::bitset<8>(state.c_str()[i]);
          }
          std::cout<< "\n####END####" << std::endl;
        }

}

}
}