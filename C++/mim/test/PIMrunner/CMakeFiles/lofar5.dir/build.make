# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Projects/ALBUS/ALBUS_ionosphere

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Projects/ALBUS/ALBUS_ionosphere

# Include any dependencies generated for this target.
include C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/compiler_depend.make

# Include the progress variables for this target.
include C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/progress.make

# Include the compile flags for this target's objects.
include C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/flags.make

C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o: C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/flags.make
C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o: C++/mim/test/PIMrunner/lofar5.cxx
C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o: C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Projects/ALBUS/ALBUS_ionosphere/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o"
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o -MF CMakeFiles/lofar5.dir/lofar5.cxx.o.d -o CMakeFiles/lofar5.dir/lofar5.cxx.o -c /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner/lofar5.cxx

C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lofar5.dir/lofar5.cxx.i"
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner/lofar5.cxx > CMakeFiles/lofar5.dir/lofar5.cxx.i

C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lofar5.dir/lofar5.cxx.s"
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner/lofar5.cxx -o CMakeFiles/lofar5.dir/lofar5.cxx.s

# Object files for target lofar5
lofar5_OBJECTS = \
"CMakeFiles/lofar5.dir/lofar5.cxx.o"

# External object files for target lofar5
lofar5_EXTERNAL_OBJECTS =

C++/mim/test/PIMrunner/lofar5: C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/lofar5.cxx.o
C++/mim/test/PIMrunner/lofar5: C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/build.make
C++/mim/test/PIMrunner/lofar5: C++/mim/test/PIMrunner/libmim.a
C++/mim/test/PIMrunner/lofar5: C++/vex_to_sky2/vexplus/libvexplus.so.1.0.0
C++/mim/test/PIMrunner/lofar5: C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/user/Projects/ALBUS/ALBUS_ionosphere/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lofar5"
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lofar5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/build: C++/mim/test/PIMrunner/lofar5
.PHONY : C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/build

C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/clean:
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner && $(CMAKE_COMMAND) -P CMakeFiles/lofar5.dir/cmake_clean.cmake
.PHONY : C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/clean

C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/depend:
	cd /home/user/Projects/ALBUS/ALBUS_ionosphere && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Projects/ALBUS/ALBUS_ionosphere /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner /home/user/Projects/ALBUS/ALBUS_ionosphere /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner /home/user/Projects/ALBUS/ALBUS_ionosphere/C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : C++/mim/test/PIMrunner/CMakeFiles/lofar5.dir/depend

