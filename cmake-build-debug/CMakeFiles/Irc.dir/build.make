# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/csherill/Documents/ExamIrc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/csherill/Documents/ExamIrc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Irc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Irc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Irc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Irc.dir/flags.make

CMakeFiles/Irc.dir/exam.cpp.o: CMakeFiles/Irc.dir/flags.make
CMakeFiles/Irc.dir/exam.cpp.o: ../exam.cpp
CMakeFiles/Irc.dir/exam.cpp.o: CMakeFiles/Irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/csherill/Documents/ExamIrc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Irc.dir/exam.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Irc.dir/exam.cpp.o -MF CMakeFiles/Irc.dir/exam.cpp.o.d -o CMakeFiles/Irc.dir/exam.cpp.o -c /Users/csherill/Documents/ExamIrc/exam.cpp

CMakeFiles/Irc.dir/exam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Irc.dir/exam.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/csherill/Documents/ExamIrc/exam.cpp > CMakeFiles/Irc.dir/exam.cpp.i

CMakeFiles/Irc.dir/exam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Irc.dir/exam.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/csherill/Documents/ExamIrc/exam.cpp -o CMakeFiles/Irc.dir/exam.cpp.s

# Object files for target Irc
Irc_OBJECTS = \
"CMakeFiles/Irc.dir/exam.cpp.o"

# External object files for target Irc
Irc_EXTERNAL_OBJECTS =

Irc: CMakeFiles/Irc.dir/exam.cpp.o
Irc: CMakeFiles/Irc.dir/build.make
Irc: CMakeFiles/Irc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/csherill/Documents/ExamIrc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Irc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Irc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Irc.dir/build: Irc
.PHONY : CMakeFiles/Irc.dir/build

CMakeFiles/Irc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Irc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Irc.dir/clean

CMakeFiles/Irc.dir/depend:
	cd /Users/csherill/Documents/ExamIrc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/csherill/Documents/ExamIrc /Users/csherill/Documents/ExamIrc /Users/csherill/Documents/ExamIrc/cmake-build-debug /Users/csherill/Documents/ExamIrc/cmake-build-debug /Users/csherill/Documents/ExamIrc/cmake-build-debug/CMakeFiles/Irc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Irc.dir/depend

