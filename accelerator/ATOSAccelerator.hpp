/***********************************************************************************
 * Copyright (c) 2017, UT-Battelle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * Neither the name of the xacc nor the
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
#ifndef ATOS_ATOS_HPP_
#define ATOS_ATOS_HPP_

#include "XACC.hpp"
#include "ATOSVisitor.hpp"

using namespace xacc;

namespace xacc {
namespace quantum {

class ATOSAccelerator: public Accelerator {
public:

	ATOSAccelerator(){}

	virtual void initialize(){
		//if (xacc::optionExists("atos-verbose")) {
		//	__verbose = 1;
		//} else {
		//	__verbose = 0;
		//}

	}

	std::shared_ptr<AcceleratorBuffer> createBuffer(const std::string& varId);

	std::shared_ptr<AcceleratorBuffer> createBuffer(const std::string& varId,
			const int size);

	virtual bool isValidBufferSize(const int NBits);

	//virtual const double getExecutionTime() {
	//	if (visitor) return visitor->getExecutionTime();
	//	else return 0.0;
	//}

	virtual void execute(std::shared_ptr<AcceleratorBuffer> buffer,
			const std::shared_ptr<xacc::Function> kernel);

	virtual std::vector<std::shared_ptr<AcceleratorBuffer>> execute(
			std::shared_ptr<AcceleratorBuffer> buffer,
			const std::vector<std::shared_ptr<Function>> functions);

	/**
 * 	 * Return all relevant ATOS runtime options.
 * 	 	 */
	virtual std::shared_ptr<options_description> getOptions() {
		auto desc = std::make_shared<options_description>(
				"ATOS Accelerator Options");
		desc->add_options()("atos-visitor", value<std::string>(),
				"Provide visitor to be used in mapping IR to circuit.")
				("atos-list-visitors", "List the available visitors.");//("atos-verbose","")
				//("atos-one-qubit-gatetime", value<std::string>(), "The runtime in seconds for a single qubit gate.")
				//("atos-two-qubit-gatetime", value<std::string>(), "The runtime in seconds for a two qubit gate.");

		return desc;
	}

	virtual bool handleOptions(variables_map& map) {
		if (map.count("atos-list-visitors")) {
			//xacc::info("Available ATOS Visitor: itensor-mps");
			//xacc::info("Available ATOS Visitor: exatensor-mps");
			return true;
		}
		return false;
	}


	/**
 * 	 * This Accelerator models QPU Gate accelerators.
 * 	 	 * @return
 * 	 	 	 */

	virtual AcceleratorType getType() {
		return AcceleratorType::qpu_gate;
	}

	virtual const std::string name() const {
		return "atos";
	}

	virtual const std::string description() const {
		return "";
	}

	/**
 * 	 * We have no need to transform the IR for this Accelerator,
 * 	 	 * so return an empty list
 * 	 	 	 * @return
 * 	 	 	 	 */
	virtual std::vector<std::shared_ptr<xacc::IRTransformation>> getIRTransformations() {
		std::vector<std::shared_ptr<xacc::IRTransformation>> v;
		return v;
	}
/*
	virtual bool isPhysical() {
		return false;
	}
*/
	/**
 * 	 * The destructor
 * 	 	 */
	virtual ~ATOSAccelerator() {
	}
/*
    int verbose() const {return __verbose; }
	void verbose(int level) {__verbose = level;}
	void set_verbose(int level) {__verbose = level;}
    void mute  () { __verbose = 0; }
    void unmute() { __verbose = 1;} // default to 1
*/
protected:

    std::shared_ptr<ATOSVisitor> visitor;

private:
	//int __verbose;
};
}
}
#endif
