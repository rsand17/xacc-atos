#include <memory>
#include <gtest/gtest.h>
#include "ATOSAccelerator.hpp"
#include "GateFunction.hpp"
#include "Hadamard.hpp"
#include "CNOT.hpp"
#include "X.hpp"

TEST(ATOSAcceleratorTester,checkKernelExecution) {

	using namespace xacc;
	using namespace xacc::quantum;

	xacc::Initialize();
	ATOSAccelerator acc;
	auto qreg1 = acc.createBuffer("qreg", 1);
	auto f = std::make_shared<GateFunction>("foo");

	auto x = std::make_shared<X>(0);
	//auto h = std::make_shared<Hadamard>(1);
	//auto cn1 = std::make_shared<CNOT>(1, 2);
	//auto cn2 = std::make_shared<CNOT>(0, 1);
	//auto h2 = std::make_shared<Hadamard>(0);
	auto m = std::make_shared<Measure>(0, 0);

	f->addInstruction(x);
	//f->addInstruction(h);
	//f->addInstruction(cn1);
	//f->addInstruction(cn2);
	//f->addInstruction(h2);
	f->addInstruction(m);

	acc.execute(qreg1, f);

	xacc::Finalize();
}
int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
