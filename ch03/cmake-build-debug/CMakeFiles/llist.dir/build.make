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
include CMakeFiles/llist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/llist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/llist.dir/flags.make

CMakeFiles/llist.dir/LList.c.o: CMakeFiles/llist.dir/flags.make
CMakeFiles/llist.dir/LList.c.o: ../LList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/llist.dir/LList.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/llist.dir/LList.c.o   -c /home/sxg/Workspace/cpp/qingdao/ch03/LList.c

CMakeFiles/llist.dir/LList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/llist.dir/LList.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sxg/Workspace/cpp/qingdao/ch03/LList.c > CMakeFiles/llist.dir/LList.c.i

CMakeFiles/llist.dir/LList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/llist.dir/LList.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sxg/Workspace/cpp/qingdao/ch03/LList.c -o CMakeFiles/llist.dir/LList.c.s

# Object files for target llist
llist_OBJECTS = \
"CMakeFiles/llist.dir/LList.c.o"

# External object files for target llist
llist_EXTERNAL_OBJECTS =

llist: CMakeFiles/llist.dir/LList.c.o
llist: CMakeFiles/llist.dir/build.make
llist: CMakeFiles/llist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable llist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/llist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/llist.dir/build: llist

.PHONY : CMakeFiles/llist.dir/build

CMakeFiles/llist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/llist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/llist.dir/clean

CMakeFiles/llist.dir/depend:
	cd /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxg/Workspace/cpp/qingdao/ch03 /home/sxg/Workspace/cpp/qingdao/ch03 /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug /home/sxg/Workspace/cpp/qingdao/ch03/cmake-build-debug/CMakeFiles/llist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/llist.dir/depend

