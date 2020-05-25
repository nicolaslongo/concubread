# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/nicolas/concubread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicolas/concubread

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nicolas/concubread/CMakeFiles /home/nicolas/concubread/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nicolas/concubread/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ConcuBread

# Build rule for target.
ConcuBread: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ConcuBread
.PHONY : ConcuBread

# fast build rule for target.
ConcuBread/fast:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/build
.PHONY : ConcuBread/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/main.cpp.s
.PHONY : main.cpp.s

src/FabricaDePan.o: src/FabricaDePan.cpp.o

.PHONY : src/FabricaDePan.o

# target to build an object file
src/FabricaDePan.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/FabricaDePan.cpp.o
.PHONY : src/FabricaDePan.cpp.o

src/FabricaDePan.i: src/FabricaDePan.cpp.i

.PHONY : src/FabricaDePan.i

# target to preprocess a source file
src/FabricaDePan.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/FabricaDePan.cpp.i
.PHONY : src/FabricaDePan.cpp.i

src/FabricaDePan.s: src/FabricaDePan.cpp.s

.PHONY : src/FabricaDePan.s

# target to generate assembly for a file
src/FabricaDePan.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/FabricaDePan.cpp.s
.PHONY : src/FabricaDePan.cpp.s

src/MaestroEspecialista.o: src/MaestroEspecialista.cpp.o

.PHONY : src/MaestroEspecialista.o

# target to build an object file
src/MaestroEspecialista.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroEspecialista.cpp.o
.PHONY : src/MaestroEspecialista.cpp.o

src/MaestroEspecialista.i: src/MaestroEspecialista.cpp.i

.PHONY : src/MaestroEspecialista.i

# target to preprocess a source file
src/MaestroEspecialista.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroEspecialista.cpp.i
.PHONY : src/MaestroEspecialista.cpp.i

src/MaestroEspecialista.s: src/MaestroEspecialista.cpp.s

.PHONY : src/MaestroEspecialista.s

# target to generate assembly for a file
src/MaestroEspecialista.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroEspecialista.cpp.s
.PHONY : src/MaestroEspecialista.cpp.s

src/MaestroPanadero.o: src/MaestroPanadero.cpp.o

.PHONY : src/MaestroPanadero.o

# target to build an object file
src/MaestroPanadero.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPanadero.cpp.o
.PHONY : src/MaestroPanadero.cpp.o

src/MaestroPanadero.i: src/MaestroPanadero.cpp.i

.PHONY : src/MaestroPanadero.i

# target to preprocess a source file
src/MaestroPanadero.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPanadero.cpp.i
.PHONY : src/MaestroPanadero.cpp.i

src/MaestroPanadero.s: src/MaestroPanadero.cpp.s

.PHONY : src/MaestroPanadero.s

# target to generate assembly for a file
src/MaestroPanadero.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPanadero.cpp.s
.PHONY : src/MaestroPanadero.cpp.s

src/MaestroPizzero.o: src/MaestroPizzero.cpp.o

.PHONY : src/MaestroPizzero.o

# target to build an object file
src/MaestroPizzero.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPizzero.cpp.o
.PHONY : src/MaestroPizzero.cpp.o

src/MaestroPizzero.i: src/MaestroPizzero.cpp.i

.PHONY : src/MaestroPizzero.i

# target to preprocess a source file
src/MaestroPizzero.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPizzero.cpp.i
.PHONY : src/MaestroPizzero.cpp.i

src/MaestroPizzero.s: src/MaestroPizzero.cpp.s

.PHONY : src/MaestroPizzero.s

# target to generate assembly for a file
src/MaestroPizzero.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MaestroPizzero.cpp.s
.PHONY : src/MaestroPizzero.cpp.s

src/MasaMadre.o: src/MasaMadre.cpp.o

.PHONY : src/MasaMadre.o

# target to build an object file
src/MasaMadre.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MasaMadre.cpp.o
.PHONY : src/MasaMadre.cpp.o

src/MasaMadre.i: src/MasaMadre.cpp.i

.PHONY : src/MasaMadre.i

# target to preprocess a source file
src/MasaMadre.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MasaMadre.cpp.i
.PHONY : src/MasaMadre.cpp.i

src/MasaMadre.s: src/MasaMadre.cpp.s

.PHONY : src/MasaMadre.s

# target to generate assembly for a file
src/MasaMadre.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/MasaMadre.cpp.s
.PHONY : src/MasaMadre.cpp.s

src/Recepcionista.o: src/Recepcionista.cpp.o

.PHONY : src/Recepcionista.o

# target to build an object file
src/Recepcionista.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Recepcionista.cpp.o
.PHONY : src/Recepcionista.cpp.o

src/Recepcionista.i: src/Recepcionista.cpp.i

.PHONY : src/Recepcionista.i

# target to preprocess a source file
src/Recepcionista.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Recepcionista.cpp.i
.PHONY : src/Recepcionista.cpp.i

src/Recepcionista.s: src/Recepcionista.cpp.s

.PHONY : src/Recepcionista.s

# target to generate assembly for a file
src/Recepcionista.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Recepcionista.cpp.s
.PHONY : src/Recepcionista.cpp.s

src/Repartidor.o: src/Repartidor.cpp.o

.PHONY : src/Repartidor.o

# target to build an object file
src/Repartidor.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Repartidor.cpp.o
.PHONY : src/Repartidor.cpp.o

src/Repartidor.i: src/Repartidor.cpp.i

.PHONY : src/Repartidor.i

# target to preprocess a source file
src/Repartidor.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Repartidor.cpp.i
.PHONY : src/Repartidor.cpp.i

src/Repartidor.s: src/Repartidor.cpp.s

.PHONY : src/Repartidor.s

# target to generate assembly for a file
src/Repartidor.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Repartidor.cpp.s
.PHONY : src/Repartidor.cpp.s

src/Trabajador.o: src/Trabajador.cpp.o

.PHONY : src/Trabajador.o

# target to build an object file
src/Trabajador.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Trabajador.cpp.o
.PHONY : src/Trabajador.cpp.o

src/Trabajador.i: src/Trabajador.cpp.i

.PHONY : src/Trabajador.i

# target to preprocess a source file
src/Trabajador.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Trabajador.cpp.i
.PHONY : src/Trabajador.cpp.i

src/Trabajador.s: src/Trabajador.cpp.s

.PHONY : src/Trabajador.s

# target to generate assembly for a file
src/Trabajador.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/src/Trabajador.cpp.s
.PHONY : src/Trabajador.cpp.s

utils/Configuracion.o: utils/Configuracion.cpp.o

.PHONY : utils/Configuracion.o

# target to build an object file
utils/Configuracion.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Configuracion.cpp.o
.PHONY : utils/Configuracion.cpp.o

utils/Configuracion.i: utils/Configuracion.cpp.i

.PHONY : utils/Configuracion.i

# target to preprocess a source file
utils/Configuracion.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Configuracion.cpp.i
.PHONY : utils/Configuracion.cpp.i

utils/Configuracion.s: utils/Configuracion.cpp.s

.PHONY : utils/Configuracion.s

# target to generate assembly for a file
utils/Configuracion.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Configuracion.cpp.s
.PHONY : utils/Configuracion.cpp.s

utils/LockFile.o: utils/LockFile.cpp.o

.PHONY : utils/LockFile.o

# target to build an object file
utils/LockFile.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/LockFile.cpp.o
.PHONY : utils/LockFile.cpp.o

utils/LockFile.i: utils/LockFile.cpp.i

.PHONY : utils/LockFile.i

# target to preprocess a source file
utils/LockFile.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/LockFile.cpp.i
.PHONY : utils/LockFile.cpp.i

utils/LockFile.s: utils/LockFile.cpp.s

.PHONY : utils/LockFile.s

# target to generate assembly for a file
utils/LockFile.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/LockFile.cpp.s
.PHONY : utils/LockFile.cpp.s

utils/Logger.o: utils/Logger.cpp.o

.PHONY : utils/Logger.o

# target to build an object file
utils/Logger.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Logger.cpp.o
.PHONY : utils/Logger.cpp.o

utils/Logger.i: utils/Logger.cpp.i

.PHONY : utils/Logger.i

# target to preprocess a source file
utils/Logger.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Logger.cpp.i
.PHONY : utils/Logger.cpp.i

utils/Logger.s: utils/Logger.cpp.s

.PHONY : utils/Logger.s

# target to generate assembly for a file
utils/Logger.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Logger.cpp.s
.PHONY : utils/Logger.cpp.s

utils/Pipe.o: utils/Pipe.cpp.o

.PHONY : utils/Pipe.o

# target to build an object file
utils/Pipe.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Pipe.cpp.o
.PHONY : utils/Pipe.cpp.o

utils/Pipe.i: utils/Pipe.cpp.i

.PHONY : utils/Pipe.i

# target to preprocess a source file
utils/Pipe.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Pipe.cpp.i
.PHONY : utils/Pipe.cpp.i

utils/Pipe.s: utils/Pipe.cpp.s

.PHONY : utils/Pipe.s

# target to generate assembly for a file
utils/Pipe.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/Pipe.cpp.s
.PHONY : utils/Pipe.cpp.s

utils/SignalHandler.o: utils/SignalHandler.cpp.o

.PHONY : utils/SignalHandler.o

# target to build an object file
utils/SignalHandler.cpp.o:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/SignalHandler.cpp.o
.PHONY : utils/SignalHandler.cpp.o

utils/SignalHandler.i: utils/SignalHandler.cpp.i

.PHONY : utils/SignalHandler.i

# target to preprocess a source file
utils/SignalHandler.cpp.i:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/SignalHandler.cpp.i
.PHONY : utils/SignalHandler.cpp.i

utils/SignalHandler.s: utils/SignalHandler.cpp.s

.PHONY : utils/SignalHandler.s

# target to generate assembly for a file
utils/SignalHandler.cpp.s:
	$(MAKE) -f CMakeFiles/ConcuBread.dir/build.make CMakeFiles/ConcuBread.dir/utils/SignalHandler.cpp.s
.PHONY : utils/SignalHandler.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... ConcuBread"
	@echo "... edit_cache"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/FabricaDePan.o"
	@echo "... src/FabricaDePan.i"
	@echo "... src/FabricaDePan.s"
	@echo "... src/MaestroEspecialista.o"
	@echo "... src/MaestroEspecialista.i"
	@echo "... src/MaestroEspecialista.s"
	@echo "... src/MaestroPanadero.o"
	@echo "... src/MaestroPanadero.i"
	@echo "... src/MaestroPanadero.s"
	@echo "... src/MaestroPizzero.o"
	@echo "... src/MaestroPizzero.i"
	@echo "... src/MaestroPizzero.s"
	@echo "... src/MasaMadre.o"
	@echo "... src/MasaMadre.i"
	@echo "... src/MasaMadre.s"
	@echo "... src/Recepcionista.o"
	@echo "... src/Recepcionista.i"
	@echo "... src/Recepcionista.s"
	@echo "... src/Repartidor.o"
	@echo "... src/Repartidor.i"
	@echo "... src/Repartidor.s"
	@echo "... src/Trabajador.o"
	@echo "... src/Trabajador.i"
	@echo "... src/Trabajador.s"
	@echo "... utils/Configuracion.o"
	@echo "... utils/Configuracion.i"
	@echo "... utils/Configuracion.s"
	@echo "... utils/LockFile.o"
	@echo "... utils/LockFile.i"
	@echo "... utils/LockFile.s"
	@echo "... utils/Logger.o"
	@echo "... utils/Logger.i"
	@echo "... utils/Logger.s"
	@echo "... utils/Pipe.o"
	@echo "... utils/Pipe.i"
	@echo "... utils/Pipe.s"
	@echo "... utils/SignalHandler.o"
	@echo "... utils/SignalHandler.i"
	@echo "... utils/SignalHandler.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

