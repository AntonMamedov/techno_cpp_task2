# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anton/dev/techno_park/cpp/task2/multi_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/dev/techno_park/cpp/task2/multi_test/build

# Include any dependencies generated for this target.
include CMakeFiles/multi_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multi_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multi_test.dir/flags.make

CMakeFiles/multi_test.dir/main.c.o: CMakeFiles/multi_test.dir/flags.make
CMakeFiles/multi_test.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/dev/techno_park/cpp/task2/multi_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/multi_test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/multi_test.dir/main.c.o   -c /home/anton/dev/techno_park/cpp/task2/multi_test/main.c

CMakeFiles/multi_test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/multi_test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/dev/techno_park/cpp/task2/multi_test/main.c > CMakeFiles/multi_test.dir/main.c.i

CMakeFiles/multi_test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/multi_test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/dev/techno_park/cpp/task2/multi_test/main.c -o CMakeFiles/multi_test.dir/main.c.s

# Object files for target multi_test
multi_test_OBJECTS = \
"CMakeFiles/multi_test.dir/main.c.o"

# External object files for target multi_test
multi_test_EXTERNAL_OBJECTS =

multi_test: CMakeFiles/multi_test.dir/main.c.o
multi_test: CMakeFiles/multi_test.dir/build.make
multi_test: ../../filemetrics_multithreaded/build/libfilemetrics.a
multi_test: CMakeFiles/multi_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/dev/techno_park/cpp/task2/multi_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable multi_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multi_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multi_test.dir/build: multi_test

.PHONY : CMakeFiles/multi_test.dir/build

CMakeFiles/multi_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multi_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multi_test.dir/clean

CMakeFiles/multi_test.dir/depend:
	cd /home/anton/dev/techno_park/cpp/task2/multi_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/dev/techno_park/cpp/task2/multi_test /home/anton/dev/techno_park/cpp/task2/multi_test /home/anton/dev/techno_park/cpp/task2/multi_test/build /home/anton/dev/techno_park/cpp/task2/multi_test/build /home/anton/dev/techno_park/cpp/task2/multi_test/build/CMakeFiles/multi_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multi_test.dir/depend

