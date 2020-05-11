#include "FabricaDePan.h"

FabricaDePan:: FabricaDePan() {

    // creo al maestroEspecialista
    maestroEspecialista = new MaestroEspecialista();
    std::string msg = "FabricaDePan: Maestro especialista creado";
    Logger::writeToLogFile(msg);

    // creo a los maestros panaderos
    for (int i = 0; i < 1; i++) {
        maestrosPanaderos.push_back(new MaestroPanadero());
    }

    //creo al maestroPizzero

    //creo al delivery

    //creo al recepcionista

}

int FabricaDePan::abrirLaFabrica() {

    int resultado;
    resultado = maestroEspecialista->jornadaLaboral();
    if (resultado == CHILD_PROCESS) {
        return resultado;
    }
    for (int i = 0; i < 1; i++) {
        resultado = maestrosPanaderos.at(i)->jornadaLaboral();
        if (resultado == CHILD_PROCESS) {
            return resultado;
        }
    }

    // same para cada proceso

    return PARENT_PROCESS;
    
}


int FabricaDePan::cerrarLaFabrica() {
    // delete log;
    std::string msg = "FabricaDePan: estamos cerrando.\n\nThis is it, fellas"; 
    Logger::writeToLogFile(msg);
    return 0;
}


FabricaDePan:: ~FabricaDePan() {
    delete maestroEspecialista;
    for(auto maestroPanadero: maestrosPanaderos) {
        delete maestroPanadero;       
    }

}
