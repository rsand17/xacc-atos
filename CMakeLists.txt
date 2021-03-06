cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(xacc-atos LANGUAGES CXX)

set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
message(STATUS "C++ version ${CXX_STANDARD} configured.")

option(ATOS_BUILD_TESTS "Build test programs" ON)

# Make sure all build libraries have reference to their dependents
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(XACC REQUIRED)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${XACC_ROOT}" CACHE PATH "default install path" FORCE )
endif()

set(CppMicroServicesConfig_DIR "${XACC_ROOT}/share/cppmicroservices4/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${XACC_ROOT}/share/xacc")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CppMicroServicesConfig_DIR}")
include(tests)
include(CppMicroServicesConfig)

include_directories(${CMAKE_BINARY_DIR})

include_directories(${XACC_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(/opt/qat/dev/include/qat/comm)
link_directories(/opt/qat/dev/lib64)

link_directories(${XACC_LIBRARY_DIR})

add_subdirectory(accelerator)
if(PYTHON_INCLUDE_DIR)
   add_subdirectory(python)
endif()

if(ATOS_BUILD_TESTS)
   include_directories(${CMAKE_SOURCE_DIR}/accelerator)
   include_directories(${CMAKE_SOURCE_DIR}/utils)
#   add_subdirectory(examples)
   add_subdirectory(tests)
endif()


