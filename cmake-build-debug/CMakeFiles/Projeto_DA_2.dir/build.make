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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Projeto_DA_2.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Projeto_DA_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projeto_DA_2.dir/flags.make

CMakeFiles/Projeto_DA_2.dir/main.cpp.obj: CMakeFiles/Projeto_DA_2.dir/flags.make
CMakeFiles/Projeto_DA_2.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Projeto_DA_2.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Projeto_DA_2.dir\main.cpp.obj -c "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\main.cpp"

CMakeFiles/Projeto_DA_2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_DA_2.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\main.cpp" > CMakeFiles\Projeto_DA_2.dir\main.cpp.i

CMakeFiles/Projeto_DA_2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_DA_2.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\main.cpp" -o CMakeFiles\Projeto_DA_2.dir\main.cpp.s

CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.obj: CMakeFiles/Projeto_DA_2.dir/flags.make
CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.obj: ../Plataform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Projeto_DA_2.dir\Plataform.cpp.obj -c "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\Plataform.cpp"

CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\Plataform.cpp" > CMakeFiles\Projeto_DA_2.dir\Plataform.cpp.i

CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\Plataform.cpp" -o CMakeFiles\Projeto_DA_2.dir\Plataform.cpp.s

# Object files for target Projeto_DA_2
Projeto_DA_2_OBJECTS = \
"CMakeFiles/Projeto_DA_2.dir/main.cpp.obj" \
"CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.obj"

# External object files for target Projeto_DA_2
Projeto_DA_2_EXTERNAL_OBJECTS =

Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/main.cpp.obj
Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/Plataform.cpp.obj
Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/build.make
Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/linklibs.rsp
Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/objects1.rsp
Projeto_DA_2.exe: CMakeFiles/Projeto_DA_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Projeto_DA_2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Projeto_DA_2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projeto_DA_2.dir/build: Projeto_DA_2.exe
.PHONY : CMakeFiles/Projeto_DA_2.dir/build

CMakeFiles/Projeto_DA_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Projeto_DA_2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Projeto_DA_2.dir/clean

CMakeFiles/Projeto_DA_2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2" "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2" "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug" "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug" "C:\Users\anaca\OneDrive\Ambiente de Trabalho\Projeto_DA_2\cmake-build-debug\CMakeFiles\Projeto_DA_2.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Projeto_DA_2.dir/depend

