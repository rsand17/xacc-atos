# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/r09/cmake-install/bin/cmake

# The command to remove a file.
RM = /home/r09/cmake-install/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/r09/xacc-atos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/r09/xacc-atos/build

# Include any dependencies generated for this target.
include accelerator/CMakeFiles/xacc-atos-accelerator.dir/depend.make

# Include the progress variables for this target.
include accelerator/CMakeFiles/xacc-atos-accelerator.dir/progress.make

# Include the compile flags for this target's objects.
include accelerator/CMakeFiles/xacc-atos-accelerator.dir/flags.make

accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp: accelerator/xacc-atos-accelerator/res_0.zip
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Checking resource dependencies for xacc-atos-accelerator"
	cd /home/r09/xacc-atos/build/accelerator && /home/r09/cmake-install/bin/cmake -E copy /home/r09/.xacc/share/cppmicroservices4/cmake/CMakeResourceDependencies.cpp /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp

accelerator/xacc-atos-accelerator/res_0.zip: ../accelerator/manifest.json
accelerator/xacc-atos-accelerator/res_0.zip: /home/r09/.xacc/bin/usResourceCompiler4
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Checking resource dependencies for xacc-atos-accelerator"
	cd /home/r09/xacc-atos/accelerator && /home/r09/cmake-install/bin/cmake -E make_directory /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator
	cd /home/r09/xacc-atos/accelerator && /home/r09/.xacc/bin/usResourceCompiler4 -o /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/res_0.zip -n xacc_atos_accelerator -r manifest.json

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o: accelerator/CMakeFiles/xacc-atos-accelerator.dir/flags.make
accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o: ../accelerator/ATOSAcceleratorActivator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o -c /home/r09/xacc-atos/accelerator/ATOSAcceleratorActivator.cpp

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.i"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/r09/xacc-atos/accelerator/ATOSAcceleratorActivator.cpp > CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.i

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.s"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/r09/xacc-atos/accelerator/ATOSAcceleratorActivator.cpp -o CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.s

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.requires:

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.requires

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.provides: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.requires
	$(MAKE) -f accelerator/CMakeFiles/xacc-atos-accelerator.dir/build.make accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.provides.build
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.provides

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.provides.build: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o


accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o: accelerator/CMakeFiles/xacc-atos-accelerator.dir/flags.make
accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o: ../accelerator/ATOSAccelerator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o -c /home/r09/xacc-atos/accelerator/ATOSAccelerator.cpp

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.i"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/r09/xacc-atos/accelerator/ATOSAccelerator.cpp > CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.i

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.s"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/r09/xacc-atos/accelerator/ATOSAccelerator.cpp -o CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.s

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.requires:

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.requires

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.provides: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.requires
	$(MAKE) -f accelerator/CMakeFiles/xacc-atos-accelerator.dir/build.make accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.provides.build
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.provides

accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.provides.build: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o


accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o: accelerator/CMakeFiles/xacc-atos-accelerator.dir/flags.make
accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o: accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o -c /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.i"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp > CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.i

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.s"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp -o CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.s

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.requires:

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.requires

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.provides: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.requires
	$(MAKE) -f accelerator/CMakeFiles/xacc-atos-accelerator.dir/build.make accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.provides.build
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.provides

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.provides.build: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o


accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o: accelerator/CMakeFiles/xacc-atos-accelerator.dir/flags.make
accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o: accelerator/xacc-atos-accelerator/cppmicroservices_init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o -c /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_init.cpp

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.i"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_init.cpp > CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.i

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.s"
	cd /home/r09/xacc-atos/build/accelerator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/cppmicroservices_init.cpp -o CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.s

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.requires:

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.requires

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.provides: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.requires
	$(MAKE) -f accelerator/CMakeFiles/xacc-atos-accelerator.dir/build.make accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.provides.build
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.provides

accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.provides.build: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o


# Object files for target xacc-atos-accelerator
xacc__atos__accelerator_OBJECTS = \
"CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o" \
"CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o" \
"CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o" \
"CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o"

# External object files for target xacc-atos-accelerator
xacc__atos__accelerator_EXTERNAL_OBJECTS =

accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o
accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o
accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o
accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o
accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/build.make
accelerator/libxacc-atos-accelerator.so: /home/r09/.xacc/lib/libCppMicroServices.so.4.0.0
accelerator/libxacc-atos-accelerator.so: accelerator/CMakeFiles/xacc-atos-accelerator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/r09/xacc-atos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library libxacc-atos-accelerator.so"
	cd /home/r09/xacc-atos/build/accelerator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xacc-atos-accelerator.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Appending zipped resources to xacc-atos-accelerator"
	cd /home/r09/xacc-atos/accelerator && /home/r09/.xacc/bin/usResourceCompiler4 -b /home/r09/xacc-atos/build/accelerator/libxacc-atos-accelerator.so -z /home/r09/xacc-atos/build/accelerator/xacc-atos-accelerator/res_0.zip

# Rule to build all files generated by this target.
accelerator/CMakeFiles/xacc-atos-accelerator.dir/build: accelerator/libxacc-atos-accelerator.so

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/build

accelerator/CMakeFiles/xacc-atos-accelerator.dir/requires: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAcceleratorActivator.cpp.o.requires
accelerator/CMakeFiles/xacc-atos-accelerator.dir/requires: accelerator/CMakeFiles/xacc-atos-accelerator.dir/ATOSAccelerator.cpp.o.requires
accelerator/CMakeFiles/xacc-atos-accelerator.dir/requires: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_resources.cpp.o.requires
accelerator/CMakeFiles/xacc-atos-accelerator.dir/requires: accelerator/CMakeFiles/xacc-atos-accelerator.dir/xacc-atos-accelerator/cppmicroservices_init.cpp.o.requires

.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/requires

accelerator/CMakeFiles/xacc-atos-accelerator.dir/clean:
	cd /home/r09/xacc-atos/build/accelerator && $(CMAKE_COMMAND) -P CMakeFiles/xacc-atos-accelerator.dir/cmake_clean.cmake
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/clean

accelerator/CMakeFiles/xacc-atos-accelerator.dir/depend: accelerator/xacc-atos-accelerator/cppmicroservices_resources.cpp
accelerator/CMakeFiles/xacc-atos-accelerator.dir/depend: accelerator/xacc-atos-accelerator/res_0.zip
	cd /home/r09/xacc-atos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/r09/xacc-atos /home/r09/xacc-atos/accelerator /home/r09/xacc-atos/build /home/r09/xacc-atos/build/accelerator /home/r09/xacc-atos/build/accelerator/CMakeFiles/xacc-atos-accelerator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : accelerator/CMakeFiles/xacc-atos-accelerator.dir/depend

