#include "FabricaDePan.h"

FabricaDePan::FabricaDePan(Logger* logger, Configuracion* config) {

    // leo los pedidos de algun lado. Los levanto
    this->logger = logger;
    this->config = config;
    
    Pipe* pedidosTelefonicosDePan = new Pipe();
    this->pipes.push_back(pedidosTelefonicosDePan);
    // idem pizza

    // creo a los recepcionistas
    int CANT_RECEPCIONISTAS = this->config->getCantidadRecepcionistas();
    for (int i = 0; i < CANT_RECEPCIONISTAS; i++) {
        // los creo
        this->recepcionistas.push_back(new Recepcionista(logger, i, pedidosTelefonicosDePan));
    }
    
    std::string mensaje = "FabricaDePan: creé " + std::to_string(CANT_RECEPCIONISTAS) 
            + " MaestrosPanaderos\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // creo al maestroEspecialista
    maestroEspecialista = new MaestroEspecialista(logger, 0);
    msg = "FabricaDePan: MaestroEspecialista creado\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // creo a los maestros panaderos
    int CANT_PANADEROS = this->config->getCantidadMaestrosPanaderos();
    for (int i = 0; i < CANT_PANADEROS; i++) {
        maestrosPanaderos.push_back(new MaestroPanadero(logger, i, pedidosTelefonicosDePan));
    }
    mensaje = "FabricaDePan: creé " + std::to_string(CANT_PANADEROS) 
            + " MaestrosPanaderos\n";
    msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    //creo al maestroPizzero

    //creo al delivery

}

int FabricaDePan::abrirLaFabrica() {

    int resultado;
    resultado = maestroEspecialista->jornadaLaboral();
    if (resultado == CHILD_PROCESS) {
        return resultado;
    }
    
    int CANT_PANADEROS = this->config->getCantidadMaestrosPanaderos();
    for (int i = 0; i < CANT_PANADEROS; i++) {
        resultado = maestrosPanaderos.at(i)->jornadaLaboral();
        if (resultado == CHILD_PROCESS) {
            return resultado;
        }
    }

    int CANT_RECEPCIONSITAS = this->config->getCantidadRecepcionistas();
    for (int i = 0; i < CANT_RECEPCIONSITAS; i++) {
        resultado = recepcionistas.at(i)->jornadaLaboral();
        if (resultado == CHILD_PROCESS) {
            return resultado;
        }
    }

    std::string mensaje = "FabricaDePan: ya están todos laburando\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // same para cada proceso
    return PARENT_PROCESS;
    
}


int FabricaDePan::cerrarLaFabrica() {
    const char* msg = "FabricaDePan: estamos cerrando.\n\nThis is it, fellas\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
    return 0;
}


FabricaDePan:: ~FabricaDePan() {
    // Logger is deleted finally by main function

    for(auto recepcionista: recepcionistas) {
        delete recepcionista;       
    }

    delete maestroEspecialista;
    for(auto maestroPanadero: maestrosPanaderos) {
        delete maestroPanadero;       
    }

    for (auto pipe: pipes) {
        delete pipe;
    }
}
