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
CMAKE_COMMAND = /home/kali/Downloads/clion-2024.1/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/kali/Downloads/clion-2024.1/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kali/Downloads/Bezier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/Downloads/Bezier/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/untitled.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled.dir/flags.make

CMakeFiles/untitled.dir/Bezier.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/Bezier.cpp.o: /home/kali/Downloads/Bezier/Bezier.cpp
CMakeFiles/untitled.dir/Bezier.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/Downloads/Bezier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled.dir/Bezier.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/Bezier.cpp.o -MF CMakeFiles/untitled.dir/Bezier.cpp.o.d -o CMakeFiles/untitled.dir/Bezier.cpp.o -c /home/kali/Downloads/Bezier/Bezier.cpp

CMakeFiles/untitled.dir/Bezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/Bezier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Downloads/Bezier/Bezier.cpp > CMakeFiles/untitled.dir/Bezier.cpp.i

CMakeFiles/untitled.dir/Bezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/Bezier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Downloads/Bezier/Bezier.cpp -o CMakeFiles/untitled.dir/Bezier.cpp.s

CMakeFiles/untitled.dir/teste.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/teste.cpp.o: /home/kali/Downloads/Bezier/teste.cpp
CMakeFiles/untitled.dir/teste.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/Downloads/Bezier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/untitled.dir/teste.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/teste.cpp.o -MF CMakeFiles/untitled.dir/teste.cpp.o.d -o CMakeFiles/untitled.dir/teste.cpp.o -c /home/kali/Downloads/Bezier/teste.cpp

CMakeFiles/untitled.dir/teste.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/teste.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Downloads/Bezier/teste.cpp > CMakeFiles/untitled.dir/teste.cpp.i

CMakeFiles/untitled.dir/teste.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/teste.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Downloads/Bezier/teste.cpp -o CMakeFiles/untitled.dir/teste.cpp.s

# Object files for target untitled
untitled_OBJECTS = \
"CMakeFiles/untitled.dir/Bezier.cpp.o" \
"CMakeFiles/untitled.dir/teste.cpp.o"

# External object files for target untitled
untitled_EXTERNAL_OBJECTS =

untitled: CMakeFiles/untitled.dir/Bezier.cpp.o
untitled: CMakeFiles/untitled.dir/teste.cpp.o
untitled: CMakeFiles/untitled.dir/build.make
untitled: CMakeFiles/untitled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kali/Downloads/Bezier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable untitled"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled.dir/build: untitled
.PHONY : CMakeFiles/untitled.dir/build

CMakeFiles/untitled.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled.dir/clean

CMakeFiles/untitled.dir/depend:
	cd /home/kali/Downloads/Bezier/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/Downloads/Bezier /home/kali/Downloads/Bezier /home/kali/Downloads/Bezier/cmake-build-debug /home/kali/Downloads/Bezier/cmake-build-debug /home/kali/Downloads/Bezier/cmake-build-debug/CMakeFiles/untitled.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/untitled.dir/depend

