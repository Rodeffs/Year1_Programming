# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Apps\CLion 2022.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Apps\CLion 2022.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/lesson3.pro.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lesson3.pro.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lesson3.pro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lesson3.pro.dir/flags.make

CMakeFiles/lesson3.pro.dir/main.c.obj: CMakeFiles/lesson3.pro.dir/flags.make
CMakeFiles/lesson3.pro.dir/main.c.obj: D:/Apps/Programming/Year1/K/C\ projects\ (1\ semester)/lesson3/main.c
CMakeFiles/lesson3.pro.dir/main.c.obj: CMakeFiles/lesson3.pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lesson3.pro.dir/main.c.obj"
	"D:\Apps\CLion 2022.2.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lesson3.pro.dir/main.c.obj -MF CMakeFiles\lesson3.pro.dir\main.c.obj.d -o CMakeFiles\lesson3.pro.dir\main.c.obj -c "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\main.c"

CMakeFiles/lesson3.pro.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lesson3.pro.dir/main.c.i"
	"D:\Apps\CLion 2022.2.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\main.c" > CMakeFiles\lesson3.pro.dir\main.c.i

CMakeFiles/lesson3.pro.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lesson3.pro.dir/main.c.s"
	"D:\Apps\CLion 2022.2.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\main.c" -o CMakeFiles\lesson3.pro.dir\main.c.s

# Object files for target lesson3.pro
lesson3_pro_OBJECTS = \
"CMakeFiles/lesson3.pro.dir/main.c.obj"

# External object files for target lesson3.pro
lesson3_pro_EXTERNAL_OBJECTS =

lesson3.pro.exe: CMakeFiles/lesson3.pro.dir/main.c.obj
lesson3.pro.exe: CMakeFiles/lesson3.pro.dir/build.make
lesson3.pro.exe: CMakeFiles/lesson3.pro.dir/linklibs.rsp
lesson3.pro.exe: CMakeFiles/lesson3.pro.dir/objects1.rsp
lesson3.pro.exe: CMakeFiles/lesson3.pro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lesson3.pro.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lesson3.pro.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lesson3.pro.dir/build: lesson3.pro.exe
.PHONY : CMakeFiles/lesson3.pro.dir/build

CMakeFiles/lesson3.pro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lesson3.pro.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lesson3.pro.dir/clean

CMakeFiles/lesson3.pro.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3" "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3" "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug" "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug" "D:\Apps\Programming\Year1\K\C projects (1 semester)\lesson3\cmake-build-debug\CMakeFiles\lesson3.pro.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lesson3.pro.dir/depend

