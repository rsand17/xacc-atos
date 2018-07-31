/*********************************************************************************
 * Copyright (c) 2017, UT-Battelle
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
#ifndef QUANTUM_GATE_ACCELERATORS_ATOS_ATOSVISITOR_HPP_
#define QUANTUM_GATE_ACCELERATORS_ATOS_ATOSVISITOR_HPP_

//#include <thrift/protocol/TBinaryProtocol.h>
//#include <thrift/transport/TSimpleFileTransport.h>
//#include <thrift/transport/TTransportUtils.h>
//#include <thrift/transport/TSocket.h>

//Internal header files for data description
#include <datamodel_types.h>
#include <task_types.h>
#include <Frontend.h>

#include <iostream>
#include <string>
#include <bitset>
#include <memory>
#include "AllGateVisitor.hpp"

using namespace qat::comm::datamodel;

using namespace qat::comm;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using GateId = std::string;
using GateDictionary = std::map<GateId, GateDefinition>;// GateDictionary;

namespace xacc {
namespace quantum {

/**
 * The aTOSVisitor is an InstructionVisitor that visits
 * quantum gate instructions and creates an equivalent
 * aQasm string that can be executed by the ATOS
 * Quantum Learning Machine.
 *
 */
class ATOSVisitor: public AllGateVisitor {
protected:

	datamodel::Circuit circuit;
	
	//using GateDictionary = std::map<GateId, GateDefinition>;// GateDictionary;
        //GateDictionary gateDictionary;
        //circuit.gateDic = gateDictionary;

	/**
	 * Reference to the aQasm string
	 * this visitor is trying to construct
	 */
	//std::string aQasmStr;

	/**
	 * Reference to the classical memory address indices
	 * where measurements are recorded.
	 */
	//std::string classicalAddresses;

	//std::map<int, int> qubitToClassicalBitIndex;

	std::vector<int> measuredQubits;

	//bool includeMeasures = true;

	int numAddresses = 0;
        
	//GateDictionary gateDictionary;

public:

	ATOSVisitor() {
	  circuit.nbqbits = 1;
	  circuit.nbcbits = 1;
          //circuit.gateDic = gateDictionary;
          ComplexNumber comNum;
          ComplexNumber realOne;
          ComplexNumber realZero;
          ComplexNumber iOne;
          realOne.re = 1;
          realZero.re = 0;
          iOne.re = 0;
          iOne.im = 1;

          GateDefinition h;
          h.matrix.nRows = 2;
          h.matrix.nCols = 2;
          comNum.re = 1 / sqrt(2);
          h.matrix.data.push_back(comNum);
          h.matrix.data.push_back(comNum);
          h.matrix.data.push_back(comNum);
          comNum.re = -1 / sqrt(2);
          h.matrix.data.push_back(comNum);
          h.arity = 1;
          h.name = "H";
          circuit.gateDic.insert({"H", h});
	  //std::cout << "Thank you for creating the hadamard gate!\nMatrix arity: " << circuit.gateDic["H"].arity << std::endl;

          GateDefinition i;
          i.matrix.nRows = 2;
          i.matrix.nCols = 2;
          i.matrix.data.push_back(realOne);
          i.matrix.data.push_back(realZero);
          i.matrix.data.push_back(realZero);
          i.matrix.data.push_back(realOne);
          i.arity = 1;
          i.name = "I";
          circuit.gateDic.insert({"I", i});

          GateDefinition x;
          x.matrix.nRows = 2;
          x.matrix.nCols = 2;
          x.matrix.data.push_back(realZero);
          x.matrix.data.push_back(realOne);
          x.matrix.data.push_back(realOne);
          x.matrix.data.push_back(realZero);
          x.arity = 1;
          x.name = "X";
          circuit.gateDic.insert({"X", x});

	  GateDefinition y;
          y.matrix.nRows = 2;
          y.matrix.nCols = 2;
          y.matrix.data.push_back(realZero);
          iOne.im = -1;
          y.matrix.data.push_back(iOne);
          iOne.im = 1;
          y.matrix.data.push_back(iOne);
          y.matrix.data.push_back(realZero);
          y.arity = 1;
          y.name = "Y";
          circuit.gateDic.insert({"Y", y});

          GateDefinition z;
          z.matrix.nRows = 2;
          z.matrix.nCols = 2;
          z.matrix.data.push_back(realOne);
          z.matrix.data.push_back(realZero);
          z.matrix.data.push_back(realZero);
          realOne.re = -1;
          z.matrix.data.push_back(realOne);
          realOne.re = 1;
          z.arity = 1;
          z.name = "Z";
          circuit.gateDic.insert({"Z", z});
/*
          GateDefinition s;
          s.matrix.nRows = 2;
          s.matrix.nCols = 2;
          s.matrix.data.push_back(realOne);
          s.matrix.data.push_back(realZero);
          s.matrix.data.push_back(realZero);
          s.matrix.data.push_back(iOne);
          s.arity = 1;
          s.name = "S";
          circuit.gateDic.insert({"S", s});

          Matrix tee;
          tee.nRows = 2;
          tee.nCols = 2
          tee.push_back(realOne);
          tee.push_back(realZero);
          tee.push_back(realZero);
          iOne = M_PI / 4;
          tee.push_back(exp(iOne));
          GateDefinition t;
          t.matrix = id;
          t.arity = 1;
          t.name = "T"
          gateDictionary.insert({"T", t});
*/

	  GateDefinition cnot;
          cnot.matrix.nRows = 4;
          cnot.matrix.nCols = 4;
          cnot.matrix.data.push_back(realOne);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);

          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realOne);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);

          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realOne);

          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realZero);
          cnot.matrix.data.push_back(realOne);
          cnot.matrix.data.push_back(realZero);
          cnot.arity = 2;
          cnot.name = "CNOT";
          circuit.gateDic.insert({"CNOT", cnot});

	  /*for(int i = 0; i < 16; i++) {
	    std::cout << cnot.matrix.data[i].re << " ";
	    if(i == 3 || i == 7 || i == 11 || i == 15) {
	      std::cout << std::endl;
	    }
	  }
	  std::cout << std::endl;

	  for (auto& x: gateDictionary) {
    	    std::cout << x.first << ": " << x.second << '\n';
  	  }
	  */

	  GateDefinition cz;
          cz.matrix.nRows = 4;
          cz.matrix.nCols = 4;
          cz.matrix.data.push_back(realOne);
          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);

          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realOne);
          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);

          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realOne);
          cz.matrix.data.push_back(realZero);

          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);
          cz.matrix.data.push_back(realZero);
          realOne.re = -1;
          cz.matrix.data.push_back(realOne);
          realOne.re = 1;
          cz.arity = 2;
          cz.name = "CSIGN";
          circuit.gateDic.insert({"CSIGN", cz});

	  GateDefinition swap;
          swap.matrix.nRows = 4;
          swap.matrix.nCols = 4;
          swap.matrix.data.push_back(realOne);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);

          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realOne);
          swap.matrix.data.push_back(realZero);

          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realOne);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);

          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realZero);
          swap.matrix.data.push_back(realOne);
          swap.arity = 2;
          swap.name = "SWAP";
          circuit.gateDic.insert({"SWAP", swap});
	}
	//add gateDic

	/**
	 * Visit hadamard gates
	 */
	void visit(Hadamard& h) {
	  datamodel::Op op;
          op.gate = "H";
          op.qbits.push_back(h.bits()[0]);
          circuit.ops.push_back(op);
	  //std::cout << "Thank you for visiting the hadamard gate!\nMatrix size: " << circuit.gateDic["H"].matrix.data.size() << std::endl;
	}

	void visit(Identity& i) {
	  datamodel::Op op;
          op.gate = "I";
          op.qbits.push_back(i.bits()[0]);
          circuit.ops.push_back(op);
	}

	void visit(CZ& cz) {
	  datamodel::Op op;
          op.gate = "CSIGN";
          op.qbits.push_back(cz.bits()[0]);
          op.qbits.push_back(cz.bits()[1]);
          circuit.ops.push_back(op);
	}

	/**
	 * Visit CNOT gates
	 */
	void visit(CNOT& cn) {
	  datamodel::Op op;
          op.gate = "CNOT";
          op.qbits.push_back(cn.bits()[0]);
	  op.qbits.push_back(cn.bits()[1]);
          circuit.ops.push_back(op);
	}
	/**
	 * Visit X gates
	 */
	void visit(X& x) {
	  datamodel::Op op;
          op.gate = "X";
          op.qbits.push_back(x.bits()[0]);
          circuit.ops.push_back(op);
	}

	/**
	 *
	 */
	void visit(Y& y) {
	  datamodel::Op op;
          op.gate = "Y";
          op.qbits.push_back(y.bits()[0]);
          circuit.ops.push_back(op);
	}

	/**
	 * Visit Z gates
	 */
	void visit(Z& z) {
	  datamodel::Op op;
          op.gate = "Z";
          op.qbits.push_back(z.bits()[0]);
          circuit.ops.push_back(op);
	}

	/**
	 * Visit Measurement gates
	 */
	void visit(Measure& m) {
	  datamodel::Op op;
          op.gate = "MEAS";
	  op.type = datamodel::OpType::MEASURE;
          op.qbits.push_back(m.bits()[0]);
	  op.cbits.push_back(m.getClassicalBitIndex());
          circuit.ops.push_back(op);
	}
	/**
	 * Visit Conditional functions
	 */
	void visit(ConditionalFunction& c) {
	}

	void visit(Rx& rx) {
	  auto angleStr = boost::lexical_cast<std::string>(rx.getParameter(0));

          GateDefinition rx1;
          rx1.matrix.nRows = 2;
          rx1.matrix.nCols = 2;
          ComplexNumber iOne, realOne;
          iOne.im = -sin(boost::get<double>(rx.getParameter(0)) / 2);
          iOne.re = 0;
          realOne.re = cos(boost::get<double>(rx.getParameter(0)) / 2);
          rx1.matrix.data.push_back(realOne);
          rx1.matrix.data.push_back(iOne);
          rx1.matrix.data.push_back(iOne);
          rx1.matrix.data.push_back(realOne);
          rx1.arity = 1;
          rx1.name = "Rx_" + angleStr;
          circuit.gateDic.insert({"Rx_" + angleStr, rx1});

	  /*for(int i = 0; i < 4; i++) {
            std::cout << rx1.matrix.data[i].re << " ";
            if(i == 1 || i == 3) {
              std::cout << std::endl;
            }
          }
          std::cout << std::endl;*/

          datamodel::Op op;
          op.gate = "RX[" + angleStr + "]";
          op.qbits.push_back(rx.bits()[0]);
          circuit.ops.push_back(op);
	}

	void visit(Ry& ry) {
	  auto angleStr = boost::lexical_cast<std::string>(ry.getParameter(0));

          GateDefinition ry1;
          ry1.matrix.nRows = 2;
          ry1.matrix.nCols = 2;
          ComplexNumber realSin, realCos;
          realSin.re = -sin(boost::get<double>(ry.getParameter(0)) / 2);
          realCos.re = cos(boost::get<double>(ry.getParameter(0)) / 2);
          ry1.matrix.data.push_back(realCos);
          ry1.matrix.data.push_back(realSin);
          realSin.re = sin(boost::get<double>(ry.getParameter(0)) / 2);
          ry1.matrix.data.push_back(realSin);
          ry1.matrix.data.push_back(realCos);
          ry1.arity = 1;
          ry1.name = "Ry_" + angleStr;
          circuit.gateDic.insert({"Ry_" + angleStr, ry1});

          datamodel::Op op;
          op.gate = "RY[" + angleStr + "]";
          op.qbits.push_back(ry.bits()[0]);
          circuit.ops.push_back(op);
	}

	void visit(Rz& rz) {
	  auto angleStr = boost::lexical_cast<std::string>(rz.getParameter(0));

          GateDefinition rz1;
          rz1.matrix.nRows = 2;
          rz1.matrix.nCols = 2;
          ComplexNumber iOne, realZero;
          iOne.im = sin(boost::get<double>(rz.getParameter(0)) / 2);
          iOne.re = cos(boost::get<double>(rz.getParameter(0)) / 2);
          realZero.re = 0;
          rz1.matrix.data.push_back(iOne);
          rz1.matrix.data.push_back(realZero);
          rz1.matrix.data.push_back(realZero);
          iOne.im = -cos(boost::get<double>(rz.getParameter(0)) / 2);
          rz1.matrix.data.push_back(iOne);
          rz1.arity = 1;
          rz1.name = "Ry_" + angleStr;
          circuit.gateDic.insert({"Rz_" + angleStr, rz1});

          datamodel::Op op;
          op.gate = "RZ[" + angleStr + "]";
          op.qbits.push_back(rz.bits()[0]);
          circuit.ops.push_back(op);
	}

	void visit(CPhase& cp) {
	  //datamodel::Op op;
          //op.gate = "S";
          //op.qbits.push_back(cp.bits()[0]);
          //circuit.ops.push_back(op);
	}

	void visit(Swap& s) {
	  datamodel::Op op;
          op.gate = "SWAP";
          op.qbits.push_back(s.bits()[0]);
          op.qbits.push_back(s.bits()[1]);
          circuit.ops.push_back(op);
	}

	void visit(GateFunction& f) {
		return;
	}
	/**
	 * Return the quil string
	 */
	datamodel::Circuit getCircuit() {
		return circuit;
	}

	/**
	 * Return the classical measurement indices
	 * as a json int array represented as a string.
	 */
	std::string getClassicalAddresses() {
	}

	int getNumberOfAddresses() {
		return numAddresses;
	}

	std::vector<int> getMeasuredQubits() {
		return measuredQubits;
	}

	/**
	 * The destructor
	 */
	virtual ~ATOSVisitor() {}
};


}
}

#endif

