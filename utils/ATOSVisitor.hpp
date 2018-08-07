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

	int numAddresses;

	int nbCbits = 0;
	std::vector<Op> ops;        
	GateDictionary gateDictionary;

public:

	ATOSVisitor() {
          ComplexNumber comNum;
          ComplexNumber realOne;
          ComplexNumber realZero;
          ComplexNumber iOne;
          realOne.__set_re(1);
          realZero.__set_re(0);
          iOne.__set_re(0);
          iOne.__set_im(1);

          GateDefinition h;
	  std::vector<ComplexNumber> datah;
	  Matrix mh;
          mh.__set_nRows(2);
          mh.__set_nCols(2);
          comNum.__set_re(1 / sqrt(2));
          datah.push_back(comNum);
          datah.push_back(comNum);
          datah.push_back(comNum);
          comNum.__set_re(-1 / sqrt(2));
          datah.push_back(comNum);
	  mh.__set_data(datah);
	  h.__set_matrix(mh);
          h.__set_arity(1);
          h.__set_name("H");
	  gateDictionary.insert({"H", h});
	  
          GateDefinition i;
	  std::vector<ComplexNumber> datai;
	  Matrix mi;
          mi.__set_nRows(2);
          mi.__set_nCols(2);
          datai.push_back(realOne);
          datai.push_back(realZero);
          datai.push_back(realZero);
          datai.push_back(realOne);
	  mi.__set_data(datai);
	  i.__set_matrix(mi);
          i.__set_arity(1);
          i.__set_name("I");
          gateDictionary.insert({"I", i});
	  
          GateDefinition x;
	  std::vector<ComplexNumber> datax;
          Matrix mx;
          mx.__set_nRows(2);
          mx.__set_nCols(2);
          datax.push_back(realZero);
          datax.push_back(realOne);
          datax.push_back(realOne);
          datax.push_back(realZero);
	  mx.__set_data(datax);
	  x.__set_matrix(mx);
          x.__set_arity(1);
          x.__set_name("X");
          gateDictionary.insert({"X", x});

	  GateDefinition y;
	  std::vector<ComplexNumber> datay;
	  Matrix my;
          my.__set_nRows(2);
          my.__set_nCols(2);
          datay.push_back(realZero);
          iOne.__set_im(-1);
          datay.push_back(iOne);
          iOne.__set_im(1);
          datay.push_back(iOne);
          datay.push_back(realZero);
	  my.__set_data(datay);
	  y.__set_matrix(my);
          y.__set_arity(1);
          y.__set_name("Y");
          gateDictionary.insert({"Y", y});

          GateDefinition z;
	  std::vector<ComplexNumber> dataz;
	  Matrix mz;
          mz.__set_nRows(2);
          mz.__set_nCols(2);
          dataz.push_back(realOne);
          dataz.push_back(realZero);
          dataz.push_back(realZero);
          realOne.__set_re(-1);
          dataz.push_back(realOne);
          realOne.__set_re(1);
	  mz.__set_data(dataz);
	  z.__set_matrix(mz);
          z.__set_arity(1);
          z.__set_name("Z");
          gateDictionary.insert({"Z", z});

          GateDefinition s;
	  std::vector<ComplexNumber> datas;
	  Matrix ms;
          ms.__set_nRows(2);
          ms.__set_nCols(2);
          datas.push_back(realOne);
          datas.push_back(realZero);
          datas.push_back(realZero);
          datas.push_back(iOne);
	  ms.__set_data(datas);
	  s.__set_matrix(ms);
          s.__set_arity(1);
          s.__set_name("S");
          gateDictionary.insert({"S", s});
/*
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
	  std::vector<ComplexNumber> datacn;
	  Matrix mcn;
          mcn.__set_nRows(4);
          mcn.__set_nCols(4);
          datacn.push_back(realOne);
          datacn.push_back(realZero);
          datacn.push_back(realZero);
          datacn.push_back(realZero);

          datacn.push_back(realZero);
          datacn.push_back(realOne);
          datacn.push_back(realZero);
          datacn.push_back(realZero);

          datacn.push_back(realZero);
          datacn.push_back(realZero);
          datacn.push_back(realZero);
          datacn.push_back(realOne);

          datacn.push_back(realZero);
          datacn.push_back(realZero);
          datacn.push_back(realOne);
          datacn.push_back(realZero);
	  mcn.__set_data(datacn);
	  cnot.__set_matrix(mcn);
          cnot.__set_arity(2);
          cnot.__set_name("CNOT");
          gateDictionary.insert({"CNOT", cnot});

	  GateDefinition cz;
	  std::vector<ComplexNumber> datacz;
          Matrix mcz;
          cz.matrix.nRows = 4;
          cz.matrix.nCols = 4;
	  datacz.push_back(realOne);
          datacz.push_back(realZero);
          datacz.push_back(realZero);
          datacz.push_back(realZero);

          datacz.push_back(realZero);
          datacz.push_back(realOne);
          datacz.push_back(realZero);
          datacz.push_back(realZero);

          datacz.push_back(realZero);
          datacz.push_back(realZero);
          datacz.push_back(realOne);
          datacz.push_back(realZero);

          datacz.push_back(realZero);
          datacz.push_back(realZero);
          datacz.push_back(realZero);
          realOne.__set_re(-1);
          datacz.push_back(realOne);
          realOne.__set_re(1);
	  mcz.__set_data(datacz);
	  cz.__set_matrix(mcz);
          cz.__set_arity(2);
          cz.__set_name("CSIGN");
          gateDictionary.insert({"CSIGN", cz});

	  GateDefinition swap;
	  std::vector<ComplexNumber> datasw;
          Matrix msw;
          msw.__set_nRows(4);
          msw.__set_nCols(4);
          datasw.push_back(realOne);
          datasw.push_back(realZero);
          datasw.push_back(realZero);
          datasw.push_back(realZero);

          datasw.push_back(realZero);
          datasw.push_back(realZero);
          datasw.push_back(realOne);
          datasw.push_back(realZero);

          datasw.push_back(realZero);
          datasw.push_back(realOne);
          datasw.push_back(realZero);
          datasw.push_back(realZero);

          datasw.push_back(realZero);
          datasw.push_back(realZero);
          datasw.push_back(realZero);
          datasw.push_back(realOne);
	  msw.__set_data(datasw);
	  swap.__set_matrix(msw);
          swap.__set_arity(2);
          swap.__set_name("SWAP");
          gateDictionary.insert({"SWAP", swap});
	  
	  GateDefinition meas;
	  meas.__set_arity(1);
	  meas.__set_name("MEAS");
	  gateDictionary.insert({"MEAS", meas});

	  circuit.__set_gateDic(gateDictionary);
	}
	//add gateDic

	/**
	 * Visit hadamard gates
	 */
	void visit(Hadamard& h) {
	  datamodel::Op op;
	  std::vector<QbitId> qbitsh;
          qbitsh.push_back(h.bits()[0]);
          op.__set_gate("H");
	  op.__set_qbits(qbitsh);
          ops.push_back(op);
	  circuit.__set_ops(ops);
	  //std::cout << "Thank you for visiting the hadamard gate!\nMatrix size: " << circuit.gateDic["H"].matrix.data.size() << std::endl;
	}

	void visit(Identity& i) {
	  datamodel::Op op;
          std::vector<QbitId> qbitsi;
          qbitsi.push_back(i.bits()[0]);
          op.__set_gate("I");
          op.__set_qbits(qbitsi);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	void visit(CZ& cz) {
	  datamodel::Op op;
          std::vector<QbitId> qbitscz;
          qbitscz.push_back(cz.bits()[0]);
	  qbitscz.push_back(cz.bits()[1]);
          op.__set_gate("CSIGN");
          op.__set_qbits(qbitscz);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	/**
	 * Visit CNOT gates
	 */
	void visit(CNOT& cn) {
	  datamodel::Op op;
          std::vector<QbitId> qbitscn;
          qbitscn.push_back(cn.bits()[0]);
          qbitscn.push_back(cn.bits()[1]);
          op.__set_gate("CNOT");
          op.__set_qbits(qbitscn);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	/**
	 * Visit X gates
	 */
	void visit(X& x) {
	  datamodel::Op op;
	  std::vector<QbitId> qbitsx;
	  qbitsx.push_back(x.bits()[0]);
          op.__set_gate("X");
          op.__set_qbits(qbitsx);
	  ops.push_back(op);
          circuit.__set_ops(ops);
	}

	/**
	 *
	 */
	void visit(Y& y) {
	  datamodel::Op op;
          std::vector<QbitId> qbitsy;
          qbitsy.push_back(y.bits()[0]);
          op.__set_gate("Y");
          op.__set_qbits(qbitsy);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	/**
	 * Visit Z gates
	 */
	void visit(Z& z) {
	  datamodel::Op op;
          std::vector<QbitId> qbitsz;
          qbitsz.push_back(z.bits()[0]);
          op.__set_gate("Z");
          op.__set_qbits(qbitsz);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	/**
	 * Visit Measurement gates
	 */
	void visit(Measure& m) {
	  datamodel::Op op;
          op.__set_gate("MEAS");
	  op.__set_type(datamodel::OpType::MEASURE);
	  std::vector<QbitId> qbitsm;
          qbitsm.push_back(m.bits()[0]);
	  op.__set_qbits(qbitsm);
	  std::vector<CbitId> cbitsm;
	  cbitsm.push_back(m.getClassicalBitIndex());
	  op.__set_cbits(cbitsm);
	  ops.push_back(op);
          circuit.__set_ops(ops);
	  nbCbits++;
	  circuit.__set_nbcbits(nbCbits);  
	}
	/**
	 * Visit Conditional functions
	 */
	void visit(ConditionalFunction& c) {
	}

	void visit(Rx& rx) {
	  auto angleStr = boost::lexical_cast<std::string>(rx.getParameter(0));

          GateDefinition rotx;
	  std::vector<ComplexNumber> datarx;
	  Matrix mrx;
          mrx.__set_nRows(2);
          mrx.__set_nCols(2);
          ComplexNumber iOne, realOne;
          iOne.__set_im(-sin(boost::get<double>(rx.getParameter(0)) / 2));
          iOne.__set_re(0);
          realOne.__set_re(cos(boost::get<double>(rx.getParameter(0)) / 2));
          datarx.push_back(realOne);
          datarx.push_back(iOne);
          datarx.push_back(iOne);
          datarx.push_back(realOne);
	  mrx.__set_data(datarx);
	  rotx.__set_matrix(mrx);
          rotx.__set_arity(1);
          rotx.__set_name("RX[" + angleStr + "]");
          gateDictionary.insert({"RX[" + angleStr + "]", rotx});
	  circuit.__set_gateDic(gateDictionary);

          datamodel::Op op;
	  std::vector<QbitId> qbitsrx;
	  qbitsrx.push_back(rx.bits()[0]);
          op.__set_gate("RX[" + angleStr + "]");
	  op.__set_qbits(qbitsrx);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	void visit(Ry& ry) {
	  auto angleStr = boost::lexical_cast<std::string>(ry.getParameter(0));

          GateDefinition roty;
	  std::vector<ComplexNumber> datary;
	  Matrix mry;
          mry.__set_nRows(2);
          mry.__set_nCols(2);
          ComplexNumber realSin, realCos;
          realSin.__set_re(-sin(boost::get<double>(ry.getParameter(0)) / 2));
          realCos.__set_re(cos(boost::get<double>(ry.getParameter(0)) / 2));
          datary.push_back(realCos);
          datary.push_back(realSin);
          realSin.__set_re(sin(boost::get<double>(ry.getParameter(0)) / 2));
          datary.push_back(realSin);
          datary.push_back(realCos);
	  mry.__set_data(datary);
	  roty.__set_matrix(mry);
          roty.__set_arity(1);
          roty.__set_name("RY[" + angleStr + "]");
          gateDictionary.insert({"RY[" + angleStr + "]", roty});
	  circuit.__set_gateDic(gateDictionary);

	  datamodel::Op op;
          std::vector<QbitId> qbitsry;
          qbitsry.push_back(ry.bits()[0]);
          op.__set_gate("RY[" + angleStr + "]");
          op.__set_qbits(qbitsry);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	void visit(Rz& rz) {
	  auto angleStr = boost::lexical_cast<std::string>(rz.getParameter(0));

          GateDefinition rotz;
	  std::vector<ComplexNumber> datarz;
          Matrix mrz;
          mrz.__set_nRows(2);
          mrz.__set_nCols(2);
          ComplexNumber iOne, realZero;
          iOne.__set_im(sin(boost::get<double>(rz.getParameter(0)) / 2));
          iOne.__set_re(cos(boost::get<double>(rz.getParameter(0)) / 2));
          realZero.__set_re(0);
          datarz.push_back(iOne);
          datarz.push_back(realZero);
          datarz.push_back(realZero);
          iOne.__set_im(-cos(boost::get<double>(rz.getParameter(0)) / 2));
          datarz.push_back(iOne);
	  mrz.__set_data(datarz);
	  rotz.__set_matrix(mrz);
          rotz.__set_arity(1);
          rotz.__set_name("RZ[" + angleStr + "]");
          gateDictionary.insert({"RZ[" + angleStr + "]", rotz});
	  circuit.__set_gateDic(gateDictionary);

          datamodel::Op op;
          std::vector<QbitId> qbitsrz;
          qbitsrz.push_back(rz.bits()[0]);
          op.__set_gate("RZ[" + angleStr + "]");
          op.__set_qbits(qbitsrz);
          ops.push_back(op);
          circuit.__set_ops(ops);
	}

	void visit(CPhase& cp) {
	  //datamodel::Op op;
          //op.gate = "S";
          //op.qbits.push_back(cp.bits()[0]);
          //circuit.ops.push_back(op);
	}

	void visit(Swap& s) {
	  datamodel::Op op;
          std::vector<QbitId> qbitssw;
          qbitssw.push_back(s.bits()[0]);
          qbitssw.push_back(s.bits()[1]);
          op.__set_gate("SWAP");
          op.__set_qbits(qbitssw);
          ops.push_back(op);
          circuit.__set_ops(ops);
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

