# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\firmt\Git\BMP-File-Editor\bmp-editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bmp_editor.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/bmp_editor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bmp_editor.dir/flags.make

CMakeFiles/bmp_editor.dir/main.c.obj: CMakeFiles/bmp_editor.dir/flags.make
CMakeFiles/bmp_editor.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bmp_editor.dir/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\bmp_editor.dir\main.c.obj -c C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\main.c

CMakeFiles/bmp_editor.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bmp_editor.dir/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\main.c > CMakeFiles\bmp_editor.dir\main.c.i

CMakeFiles/bmp_editor.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bmp_editor.dir/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\main.c -o CMakeFiles\bmp_editor.dir\main.c.s

# Object files for target bmp_editor
bmp_editor_OBJECTS = \
"CMakeFiles/bmp_editor.dir/main.c.obj"

# External object files for target bmp_editor
bmp_editor_EXTERNAL_OBJECTS =

bmp_editor.exe: CMakeFiles/bmp_editor.dir/main.c.obj
bmp_editor.exe: CMakeFiles/bmp_editor.dir/build.make
bmp_editor.exe: CMakeFiles/bmp_editor.dir/linklibs.rsp
bmp_editor.exe: CMakeFiles/bmp_editor.dir/objects1.rsp
bmp_editor.exe: CMakeFiles/bmp_editor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bmp_editor.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bmp_editor.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bmp_editor.dir/build: bmp_editor.exe
.PHONY : CMakeFiles/bmp_editor.dir/build

CMakeFiles/bmp_editor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bmp_editor.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bmp_editor.dir/clean

CMakeFiles/bmp_editor.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\firmt\Git\BMP-File-Editor\bmp-editor C:\Users\firmt\Git\BMP-File-Editor\bmp-editor C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug C:\Users\firmt\Git\BMP-File-Editor\bmp-editor\cmake-build-debug\CMakeFiles\bmp_editor.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bmp_editor.dir/depend

