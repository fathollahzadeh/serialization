# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/saeed/App/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/saeed/App/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TwitterGenerateRandomList.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TwitterGenerateRandomList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TwitterGenerateRandomList.dir/flags.make

CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o: CMakeFiles/TwitterGenerateRandomList.dir/flags.make
CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o: ../src/benchmarks/source/GenerateRandomList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o"
	clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o -c /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/src/benchmarks/source/GenerateRandomList.cpp

CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/src/benchmarks/source/GenerateRandomList.cpp > CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.i

CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/src/benchmarks/source/GenerateRandomList.cpp -o CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.s

# Object files for target TwitterGenerateRandomList
TwitterGenerateRandomList_OBJECTS = \
"CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o"

# External object files for target TwitterGenerateRandomList
TwitterGenerateRandomList_EXTERNAL_OBJECTS =

../bin/TwitterGenerateRandomList: CMakeFiles/TwitterGenerateRandomList.dir/src/benchmarks/source/GenerateRandomList.cpp.o
../bin/TwitterGenerateRandomList: CMakeFiles/TwitterGenerateRandomList.dir/build.make
../bin/TwitterGenerateRandomList: CMakeFiles/TwitterGenerateRandomList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/TwitterGenerateRandomList"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TwitterGenerateRandomList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TwitterGenerateRandomList.dir/build: ../bin/TwitterGenerateRandomList

.PHONY : CMakeFiles/TwitterGenerateRandomList.dir/build

CMakeFiles/TwitterGenerateRandomList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TwitterGenerateRandomList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TwitterGenerateRandomList.dir/clean

CMakeFiles/TwitterGenerateRandomList.dir/depend:
	cd /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++ /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++ /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug /home/saeed/Documents/Projects/1-Research/GitHub/serialization/C++/cmake-build-debug/CMakeFiles/TwitterGenerateRandomList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TwitterGenerateRandomList.dir/depend

