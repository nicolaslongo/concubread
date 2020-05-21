#include "FabricaDePan.h"

FabricaDePan::FabricaDePan(Logger* logger) {

    // leo los pedidos de algun lado. Los levanto
    this->logger = logger;

    // creo a los recepcionistas
    for (int i = 0; i < 1; i++) {
        // los creo
    }
    
    // creo al maestroEspecialista
    maestroEspecialista = new MaestroEspecialista(logger);
    const char* msg = "FabricaDePan: MaestroEspecialista creado\n";
    while(this->logger->lockLogger() == -1) sched_yield();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // creo a los maestros panaderos
    for (int i = 0; i < 1; i++) {
        maestrosPanaderos.push_back(new MaestroPanadero());
    const char* msg = "FabricaDePan: iésimo MaestroPanadero creado\n";
    while(this->logger->lockLogger() == -1) sched_yield();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
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
    const char* msg = "FabricaDePan: estamos cerrando.\n\nThis is it, fellas\n";
    while(this->logger->lockLogger() == -1) sched_yield();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
    return 0;
}


FabricaDePan:: ~FabricaDePan() {
    // Logger is deleted finally by main function

    delete maestroEspecialista;
    for(auto maestroPanadero: maestrosPanaderos) {
        delete maestroPanadero;       
    }

}
