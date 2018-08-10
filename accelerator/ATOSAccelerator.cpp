/***********************************************************************************
 * Copyright (c) 2017, UT-Battelle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *   * Neither the name of the xacc nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * Contributors:
 * Initial API and implementation - Ryan Sand, Alex McCaskey
 *
 ***********************************************************************************/

#include "ATOSAccelerator.hpp"
#include <qat/core/circuit.h>
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

void ATOSAccelerator::execute(std::shared_ptr<AcceleratorBuffer> buffer, const std::shared_ptr<xacc::Function> kernel) {

	std::cout << "Executing KERNEL: " << kernel->name() << "\n";
	auto visitor = std::make_shared<ATOSVisitor>();
	datamodel::Circuit circuit;
	
	std::cout << "Made Visitor" << std::endl;

	InstructionIterator it(kernel);
	while (it.hasNext()) {
		auto nextInst = it.next();
		if (nextInst->isEnabled()) {
			nextInst->accept(visitor);
		}
	}

	std::cout << "Iterated over IR" << std::endl;

	circuit = visitor->getCircuit();
	circuit.__set_nbqbits(buffer->size());
	circuit.__set_nbcbits(buffer->size());
	std::vector<qpu::Result> results;
	task::Task task;
	task.__set_circuit(circuit);
	qpu::exec_options options;
	std::vector<int> qbits(circuit.nbqbits);

	for (int i = 0; i < circuit.nbqbits; i++) {
          qbits[i] = i;
        }

        options.__set_qbits(qbits);
	options.__set_run_nb(10);

	std::cout << "Circuit ops: " << circuit.ops << std::endl;
	std::cout << "Circuit num qbits: " << circuit.nbqbits << std::endl;
	std::cout << "Circuit num cbits: " << circuit.nbcbits << std::endl;

	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 21290));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	qpu::FrontendClient qpu_client(protocol);
        transport->open();

	std::cout << "Did Transport Protocol stuff" << std::endl;
	//qpu::FrontendClient qpu = qpu_client("localhost", 21290);

	//write_circuit(circuit, "program_circ.circ");
	
	qpu_client.Execute(results, task, options);

	std::cout << "Called Execute" << std::endl;
	for ( auto result : results) {
          std::cout << "####BEGIN####\n" << result << std::endl;
          std::string state = result.state;
	  std::string bufferBits;
	  for(int i = circuit.nbqbits - 1; i >= 0; i--) {
	    bool bitResult = std::bitset<8>(state.c_str()[0])[i];
	    if(bitResult) {
	      bufferBits += "1";
	    }
	    else {
	      bufferBits += "0";
	    }
	  }
	  buffer->appendMeasurement(bufferBits);
	  std::cout << "ACCBUF: " << bufferBits << "\n"; //buffer->getMeasurementStrings() << std::endl;
          std::cout << "binary state [ qbit_"<< state.size() * 8 << ", qbit_" << 0 << "]: " << std::endl;
          //for (std::size_t i = 0; i < state.size(); ++i)
          //{
            std:: cout << std::bitset<8>(state.c_str()[0]);
          //}
	  std::cout<< "\n####END####" << std::endl;
        }
	
	transport->close();
}

}
}
