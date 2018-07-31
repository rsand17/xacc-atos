#include "ATOSAccelerator.hpp"

#include "cppmicroservices/BundleActivator.h"
#include "cppmicroservices/BundleContext.h"
#include "cppmicroservices/ServiceProperties.h"

#include <memory>
#include <set>

using namespace cppmicroservices;

namespace {

/**
 *  */
class US_ABI_LOCAL ATOSAcceleratorActivator: public BundleActivator {

public:

	ATOSAcceleratorActivator() {
	}

	/**
 * 	 */
	void Start(BundleContext context) {
		auto acc = std::make_shared<xacc::quantum::ATOSAccelerator>();
		context.RegisterService<xacc::Accelerator>(acc);
		context.RegisterService<xacc::OptionsProvider>(acc);
	}

	/**
 * 	 */
	void Stop(BundleContext /*context*/) {
	}

};

}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ATOSAcceleratorActivator)

