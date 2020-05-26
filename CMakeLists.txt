cmake_minimum_required(VERSION 2.8)
project(ConcuBread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -ggdb")
add_executable(ConcuBread main.cpp 
src/MaestroEspecialista.cpp
src/MaestroPanadero.cpp
src/MaestroPizzero.cpp
src/Recepcionista.cpp
src/Repartidor.cpp
src/Trabajador.cpp
src/MasaMadre.cpp
src/FabricaDePan.cpp
utils/Logger.cpp
utils/LockFile.cpp
utils/Configuracion.cpp
utils/Pipe.cpp
utils/SignalHandler.cpp)