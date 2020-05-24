#include "FabricaDePan.h"

FabricaDePan::FabricaDePan(Logger* logger, Configuracion* config) {

    // leo los pedidos de algun lado. Los levanto
    this->logger = logger;
    this->config = config;

    Pipe* listaDePedidos = new Pipe();
    this->listaDePedidos = listaDePedidos;
    this->pipes.push_back(listaDePedidos);

    Pipe* pedidosTelefonicosDePan = new Pipe();
    this->pipes.push_back(pedidosTelefonicosDePan);

    Pipe* pedidosTelefonicosDePizza = new Pipe();
    this->pipes.push_back(pedidosTelefonicosDePizza);

    // creo a los recepcionistas
    int CANT_RECEPCIONISTAS = this->config->getCantidadRecepcionistas();
    for (int i = 0; i < CANT_RECEPCIONISTAS; i++) {
        // los creo
        this->recepcionistas.push_back(new Recepcionista(logger, i, listaDePedidos,
                                        pedidosTelefonicosDePan, pedidosTelefonicosDePizza));
    }
    
    // creo al maestroEspecialista
    maestroEspecialista = new MaestroEspecialista(logger, 0);

    // creo a los maestros panaderos
    int CANT_PANADEROS = this->config->getCantidadMaestrosPanaderos();
    for (int i = 0; i < CANT_PANADEROS; i++) {
        maestrosPanaderos.push_back(new MaestroPanadero(logger, i, pedidosTelefonicosDePan));
    }

    // creo a los maestros pizzeros
    int CANT_PIZZEROS = this->config->getCantidadMaestrosPizzeros();
    for (int i = 0; i < CANT_PIZZEROS; i++) {
        maestrosPizzeros.push_back(new MaestroPizzero(logger, i, pedidosTelefonicosDePizza));
    }

    std::string mensaje = "FabricaDePan: creé " + std::to_string(CANT_PANADEROS) 
            + " MaestrosPanaderos, " + std::to_string(CANT_PIZZEROS) 
            + " MaestrosPizzeros, " + std::to_string(CANT_RECEPCIONISTAS)
            + " Recepcionistas, \n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    //creo al delivery

}

void FabricaDePan::despacharPedidosALaListaDePedidos() {

    std::string name = (string(PEDIDOS_FILE_FOLDER) + "pedidos.txt");
    FILE* file = fopen(name.c_str() , "r");
    if(file == NULL) {
        const char* msg = "Error abriendo el archivo de configuracion. Nada de esto puede suceder.\n";
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    char* read_pointer = (char*) malloc( TO_READ * sizeof(char*) );
    memset(read_pointer, 0, TO_READ * sizeof(char*));

    
    // Lectura adelantada
    char * result = fgets(read_pointer, TO_READ, file );
    while (result != NULL) {
        //this->listaDePedidos->lockPipe();
        this->listaDePedidos->escribir( (const void *) read_pointer, strlen(read_pointer) );
        std::cout << "Fabrica de pan: escribi " << std::string(read_pointer) << " en el pipe " << endl;
        //this->listaDePedidos->unlockPipe();
        result = fgets(read_pointer, TO_READ, file );
    }

}

int FabricaDePan::abrirLaFabrica() {

    int resultado;
    
    int CANT_PANADEROS = this->config->getCantidadMaestrosPanaderos();
    for (int i = 0; i < CANT_PANADEROS; i++) {
        resultado = maestrosPanaderos.at(i)->jornadaLaboral();
        if (resultado == CHILD_PROCESS) {
            return resultado;
        }
    }

    int CANT_PIZZEROS = this->config->getCantidadMaestrosPizzeros();
    for (int i = 0; i < CANT_PIZZEROS; i++) {
        resultado = maestrosPizzeros.at(i)->jornadaLaboral();
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

    // Ningún child process llega hasta acá. Solo el parent Process. Este se encargará de darle vida
    // al maestroEspecialista
    despacharPedidosALaListaDePedidos();

    std::string mensaje = "FabricaDePan: ya están todos laburando. Arranca un poco más tarde el Maestro Especialista\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // Esto quisiera que vaya al thread principal
    resultado = maestroEspecialista->jornadaLaboral();
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
    for(auto maestroPizzero: maestrosPizzeros) {
        delete maestroPizzero;       
    }

    for (auto pipe: pipes) {
        delete pipe;
    }
}
