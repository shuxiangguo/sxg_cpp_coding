# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/opt/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/opt/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sxg/Workspace/cpp/qingdao/ch03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/slist2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/slist2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slist2.dir/flags.make

CMakeFiles/slist2.dir/slist.cpp.o: CMakeFiles/slist2.dir/flags.make
CMakeFiles/slist2.dir/slist.cpp.o: ../slist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/slist2.dir/slist.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slist2.dir/slist.cpp.o -c /home/sxg/Workspace/cpp/qingdao/ch03/slist.cpp

CMakeFiles/slist2.dir/slist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slist2.dir/slist.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sxg/Workspace/cpp/qingdao/ch03/slist.cpp > CMakeFiles/slist2.dir/slist.cpp.i

CMakeFiles/slist2.dir/slist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slist2.dir/slist.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sxg/Workspace/cpp/qingdao/ch03/slist.cpp -o CMakeFiles/slist2.dir/slist.cpp.s

# Object files for target slist2
slist2_OBJECTS = \
"CMakeFiles/slist2.dir/slist.cpp.o"

# External object files for target slist2
slist2_EXTERNAL_OBJECTS =

slist2: CMakeFiles/slist2.dir/slist.cpp.o
slist2: CMakeFiles/slist2.dir/build.make
slist2: CMakeFiles/slist2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable slist2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slist2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slist2.dir/build: slist2

.PHONY : CMakeFiles/slist2.dir/build

CMakeFiles/slist2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slist2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slist2.dir/clean

CMakeFiles/slist2.dir/depend:
	cd /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxg/Workspace/cpp/qingdao/ch03 /home/sxg/Workspace/cpp/qingdao/ch03 /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles/slist2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/slist2.dir/depend

