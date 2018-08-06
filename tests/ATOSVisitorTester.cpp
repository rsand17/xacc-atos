/* Copyright (c) 2017, UT-Battelle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the xacc nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
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
 *
 * Contributors:
 *   Initial API and implementation - Ryan Sand, Alex McCaskey
 *
 **********************************************************************************/
#include <memory>
#include <string>
#include <gtest/gtest.h>
#include "ATOSVisitor.hpp"
#include "InstructionIterator.hpp"

#include <datamodel_types.h>
#include <task_types.h>
#include <Frontend.h>

using namespace xacc;
using namespace xacc::quantum;
//using GateId = std::string;

TEST(ATOSVisitorTester,checkIRToATOS) {
	datamodel::Circuit circuit;
	std::vector<std::string> expect;
	std::vector<int> expectb;

	auto f = std::make_shared<GateFunction>("foo");

	auto x = std::make_shared<X>(0);
	expect.push_back("X");
	expectb.push_back(0);
/*
	auto y = std::make_shared<Y>(0);
	expect.push_back("Y");
	expectb.push_back(0);
	auto z = std::make_shared<Z>(0);
	expect.push_back("Z");
	expectb.push_back(0);
	auto i = std::make_shared<Identity>(0);
	expect.push_back("I");
	expectb.push_back(0);
*/
	auto h = std::make_shared<Hadamard>(0);
	expect.push_back("H");
	expectb.push_back(0);
/*
	auto cn1 = std::make_shared<CNOT>(1, 2);
	expect.push_back("CNOT");
	expectb.push_back(0);
	auto cn2 = std::make_shared<CNOT>(0, 1);
	expect.push_back("CNOT");
	expectb.push_back(0);
	auto h2 = std::make_shared<Hadamard>(0);
	expect.push_back("H");
	expectb.push_back(0);
	auto rx = std::make_shared<Rx>(0, M_PI);
	expect.push_back("RX[3.14159]");
	expectb.push_back(0);
	auto ry = std::make_shared<Ry>(0, M_PI);
	expect.push_back("RY[3.14159]");
	expectb.push_back(0);
	auto rz = std::make_shared<Rz>(0, M_PI);
	expect.push_back("RZ[3.14159]");
	expectb.push_back(0);
	auto swap1 = std::make_shared<Swap>(1, 2);
	expect.push_back("SWAP");
	auto swap2 = std::make_shared<Swap>(0, 1);
	expect.push_back("SWAP");
	auto cz1 = std::make_shared<CZ>(1, 2);
	expect.push_back("CSIGN");
	auto cz2 = std::make_shared<CZ>(0, 1);
	expect.push_back("CSIGN");
	//auto s = std::make_shared<CPhase>(0);
*/
	auto m0 = std::make_shared<Measure>(0, 0);
	expect.push_back("MEAS");
//	auto m1 = std::make_shared<Measure>(1,1);
//	expect.push_back("MEAS");

	//auto cond1 = std::make_shared<ConditionalFunction>(0);
	//auto z = std::make_shared<Z>(2);
	//cond1->addInstruction(z);
	//auto cond2 = std::make_shared<ConditionalFunction>(1);
	//auto x2 = std::make_shared<X>(2);
	//cond2->addInstruction(x2);

	f->addInstruction(x);
//	f->addInstruction(y);
//	f->addInstruction(z);
//	f->addInstruction(i);
	f->addInstruction(h);
//	f->addInstruction(cn1);
//	f->addInstruction(cn2);
//	f->addInstruction(h2);
//	f->addInstruction(rx);
//	f->addInstruction(ry);
//	f->addInstruction(rz);
//	f->addInstruction(swap1);
//	f->addInstruction(swap2);
//	f->addInstruction(cz1);
//	f->addInstruction(cz2);
	//f->addInstruction(s);
	f->addInstruction(m0);
//	f->addInstruction(m1);
	//f->addInstruction(cond1);
	//f->addInstruction(cond2);


	// Create the Instruction Visitor that is going
	// to map our IR to Quil.
	auto visitor = std::make_shared<ATOSVisitor>();

	// Our QIR is really a tree structure
	// so create a pre-order tree traversal
	// InstructionIterator to walk it
	InstructionIterator it(f);
	while (it.hasNext()) {
		// Get the next node in the tree
		auto nextInst = it.next();
		if (nextInst->isEnabled())
			nextInst->accept(visitor);
	}
	
	std::stringstream ss;
	circuit = visitor->getCircuit();
	for(int i = 0; i < circuit.ops.size(); i++) {
	  std::cout << "GateID = " << circuit.gateDic[circuit.ops[i].gate] << std::endl;
	  //std::cout << circuit.gateDic[circuit.ops[i].gate].matrix.data.size() << std::endl;
	  if(circuit.gateDic[circuit.ops[i].gate].arity == 2) {
	    ss << circuit.ops[i].gate << " q[" << circuit.ops[i].qbits[0] << "],q[" << circuit.ops[i].qbits[1] << "]\n";
	    std::string result = circuit.ops[i].gate;
	    EXPECT_TRUE(!result.compare(expect[i]));
	    //Matrix matrix = circuit.gateDic["CNOT"].matrix;
	    /*
	    for(int j = 0; j < circuit.gateDic[circuit.ops[i].gate].matrix.data.size(); j++){
	      ss << circuit.gateDic[circuit.ops[i].gate].matrix.data[j].re << "+" << circuit.gateDic[circuit.ops[i].gate].matrix.data[j].im << "i ";
	      if(j == 3 || j == 7 || j == 11 || j == 15) {
		ss::cout << std::endl;
	      }
	    }
	    ss::cout << std::endl;
	    */
	  } else if(circuit.ops[i].gate.compare("MEAS")) {
	    ss << circuit.ops[i].gate << " q[" << circuit.ops[i].qbits[0] << "]\n";
	    std::string result = circuit.ops[i].gate;
	    EXPECT_TRUE(!result.compare(expect[i]));
	    EXPECT_TRUE(circuit.ops[i].qbits[0] == expectb[i]);
	    
            for(int j = 0; j < circuit.gateDic[circuit.ops[i].gate].matrix.data.size(); j++){
              ss << std::setprecision(3) << circuit.gateDic[circuit.ops[i].gate].matrix.data[j].re << "+" << circuit.gateDic[circuit.ops[i].gate].matrix.data[j].im << "i ";
              if(j == 1 || j == 3) {
                ss << std::endl;
              }
	    }
	    ss << std::endl;
	    
	  }else{
	    ss << circuit.ops[i].gate << " q[" << circuit.ops[i].qbits[0] << "] c[" << circuit.ops[i].cbits[0] << "]\n"; 
	    std::string result = circuit.ops[i].gate;
	    EXPECT_TRUE(!result.compare(expect[i]));
	    //ss << std::endl;
	  }
	}
	std::cout << "\nACTUAL:\n" << ss.str() << std::endl;
	const std::string expected =
		"X q[0]\n"
		"Y q[0]\n"
		"Z q[0]\n"
		"I q[0]\n"
		"H q[0]\n"
		"CNOT q[1],q[2]\n"
		"CNOT q[0],q[1]\n"
		"H q[0]\n"
		"RX[3.14159] q[0]\n"
		"RY[3.14159] q[0]\n"
		"RZ[3.14159] q[0]\n"
		"SWAP q[1],q[2]\n"
		"SWAP q[0],q[1]\n"
		"CSIGN q[1],q[2]\n"
		"CSIGN q[0],q[1]\n"
		"MEAS q[0] c[0]\n"
		"MEAS q[1] c[1]\n";

	std::cout << "EXPECTED:\n" << expected << "\n";
	EXPECT_TRUE(!expected.compare(ss.str()));
//	EXPECT_TRUE()
}


int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

