#include "FabricaDePan.h"

FabricaDePan::FabricaDePan(Logger* logger, Configuracion* config) {

    this->logger = logger;
    this->config = config;

    // encapsular en abrir pipes //
    // la otra es crear un vector acá nuevo y usar ese, a ver qué pasa
    std::vector <Pipe*> *vector_de_pipes = (std::vector <Pipe*>*) malloc( sizeof(std::vector<Pipe*>) *
                                                                         (PIPE_CAJAS_PARA_ENTREGAR+1) );

    Pipe* listaDePedidos = new Pipe();
    this->listaDePedidos = listaDePedidos;
    vector_de_pipes->push_back(listaDePedidos);

    Pipe* pedidosTelefonicosDePan = new Pipe();
    vector_de_pipes->push_back(pedidosTelefonicosDePan);

    Pipe* pedidosTelefonicosDePizza = new Pipe();
    vector_de_pipes->push_back(pedidosTelefonicosDePizza);

    Pipe* pedidosMasaMadre = new Pipe();
    vector_de_pipes->push_back(pedidosMasaMadre);

    Pipe* entregasMasaMadre = new Pipe();
    vector_de_pipes->push_back(entregasMasaMadre);

    Pipe* cajasParaEntregar = new Pipe();
    vector_de_pipes->push_back(cajasParaEntregar);

    std::cout << "Este es el largo de pipes " << vector_de_pipes->size() << endl;

    // creo al maestroEspecialista
    maestroEspecialista = new MaestroEspecialista(logger, 0, vector_de_pipes);

    // creo a los recepcionistas
    int CANT_RECEPCIONISTAS = this->config->getCantidadRecepcionistas();
    for (int i = 0; i < CANT_RECEPCIONISTAS; i++) {
        this->recepcionistas.push_back(new Recepcionista(logger, i, vector_de_pipes));
    }
    
    // creo a los maestros panaderos
    int CANT_PANADEROS = this->config->getCantidadMaestrosPanaderos();
    for (int i = 0; i < CANT_PANADEROS; i++) {
        maestrosPanaderos.push_back(new MaestroPanadero(logger, i, vector_de_pipes));
    }

    // creo a los maestros pizzeros
    int CANT_PIZZEROS = this->config->getCantidadMaestrosPizzeros();
    for (int i = 0; i < CANT_PIZZEROS; i++) {
        maestrosPizzeros.push_back(new MaestroPizzero(logger, i, vector_de_pipes));
    }

    //creo al delivery
    int CANT_REPARTIDORES = this->config->getCantidadRepartidores();
    for (int i = 0; i < CANT_REPARTIDORES; i++) {
        repartidores.push_back(new Repartidor(logger, i, vector_de_pipes));
    }

    std::string mensaje = "FabricaDePan: creé " + std::to_string(CANT_PANADEROS) 
            + " MaestrosPanaderos, " + std::to_string(CANT_PIZZEROS) 
            + " MaestrosPizzeros, " + std::to_string(CANT_RECEPCIONISTAS)
            + " Recepcionistas, " + std::to_string (CANT_REPARTIDORES) 
            + " Repartidores, y por supuesto al MaestroEspecialista.\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
}

void FabricaDePan::abrirLaLineaTelefonicaParaPedidos() {

    std::string name = (string(PEDIDOS_FILE_FOLDER) + this->config->getArchivoDePedidos() );
    FILE* file = fopen(name.c_str() , "r");
    if(file == NULL) {
        const char* msg = "Error abriendo el archivo de configuracion. Probablemente se indicó mal el nombre del mismo.\n";
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
        this->listaDePedidos->escribir( (const void *) read_pointer, strlen(read_pointer) );
        result = fgets(read_pointer, TO_READ, file );
    }

    free(read_pointer);

    if ( fclose(file) < 0 ) {
        const char* msg = "Error cerrando el archivo de configuración. Esto se traducirá en un memory leak.\n";
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
    };

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

    int CANT_REPARTIDORES = this->config->getCantidadRepartidores();
    for (int i = 0; i < CANT_REPARTIDORES; i++) {
        resultado = repartidores.at(i)->jornadaLaboral();
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

    // Ningún child process llega hasta acá. Solo el parent Process.
    // Este se encargará de darle vida próximamente al maestroEspecialista
    abrirLaLineaTelefonicaParaPedidos();

    std::string mensaje = "FabricaDePan: ya están todos laburando. Arranca un poco más tarde el Maestro Especialista\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    resultado = maestroEspecialista->jornadaLaboral();
    return PARENT_PROCESS;
}


int FabricaDePan::cerrarLaFabrica() {

    std::cout << "\nFabricaDePan: estamos cerrando" << endl;
    const char* msg = "FabricaDePan: estamos cerrando.\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
    return 0;
}


FabricaDePan:: ~FabricaDePan() {

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

    for(auto repartidor: repartidores) {
        delete repartidor;       
    }

    for (auto pipe: pipes) {
        pipe->cerrar();
        delete pipe;
    }
}
