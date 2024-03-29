#include "Configuracion.h"

Configuracion::Configuracion(Logger* logger) {

    this->logger = logger;
    std::string name = (string(CONFIG_FILE_FOLDER) + "config.txt");
    this->file = fopen(name.c_str() , "r");
    if(file == NULL) {
        const char* msg = "Error abriendo el archivo de configuracion. Nada de esto puede suceder.\n";
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    try {
        leerConfigFile();
    } catch ( std::string& mensaje ) {
        throw mensaje;
    }
}

void Configuracion::leerConfigFile(){

    leerCantidadRecepcionistas();

    leerCantidadMaestrosPanaderos();

    leerCantidadMaestrosPizzeros();

    leerCantidadRepartidores();

    leerArchivoDePedidos();
    
}

void Configuracion::leerCantidadRecepcionistas() {

    char* max_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(max_pointer, 0, MAX_READ * sizeof(char*));

    char* min_pointer = (char*) malloc( MIN_READ * sizeof(char*) );
    memset(min_pointer, 0, MIN_READ * sizeof(char*));

    // Leo la cantidad de Recepcionistas
    if (fgets(max_pointer, MAX_READ, this->file) != NULL) {
        if (fgets(min_pointer, MIN_READ, this->file) != NULL) {
            this->cantidadRecepcionistas = atoi(min_pointer);

            std::string mensaje = "Configuracion: " 
                + std::string(max_pointer)
                + std::to_string(this->cantidadRecepcionistas) + ".\n";
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
    }
    free(max_pointer);
    free(min_pointer);
}

void Configuracion::leerCantidadMaestrosPanaderos() {
    char* max_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(max_pointer, 0, MAX_READ * sizeof(char*));

    char* min_pointer = (char*) malloc( MIN_READ * sizeof(char*) );
    memset(min_pointer, 0, MIN_READ * sizeof(char*));

    // Leo la cantidad de Maestros Panaderos
    if (fgets(max_pointer, MAX_READ, this->file) != NULL) {
        if (fgets(min_pointer, MIN_READ, this->file) != NULL) {
            this->cantidadMaestrosPanaderos = atoi(min_pointer);

            std::string mensaje = "Configuracion: " 
                + std::string(max_pointer) 
                + std::to_string(this->cantidadMaestrosPanaderos) + ".\n";
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
    }

    free(max_pointer);
    free(min_pointer);

}

void Configuracion::leerCantidadMaestrosPizzeros() {
    char* max_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(max_pointer, 0, MAX_READ * sizeof(char*));

    char* min_pointer = (char*) malloc( MIN_READ * sizeof(char*) );
    memset(min_pointer, 0, MIN_READ * sizeof(char*));

    // Leo la cantidad de Maestros Pizzeros
    if (fgets(max_pointer, MAX_READ, this->file) != NULL) {
        if (fgets(min_pointer, MIN_READ, this->file) != NULL) {
            this->cantidadMaestrosPizzeros = atoi(min_pointer);

            std::string mensaje = "Configuracion: " 
                + std::string(max_pointer) 
                + std::to_string(this->cantidadMaestrosPizzeros) + ".\n";
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
    }

    free(max_pointer);
    free(min_pointer);

}

void Configuracion::leerCantidadRepartidores() {

    char* max_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(max_pointer, 0, MAX_READ * sizeof(char*));

    char* min_pointer = (char*) malloc( MIN_READ * sizeof(char*) );
    memset(min_pointer, 0, MIN_READ * sizeof(char*));

    // Leo la cantidad de Repartidores
    if (fgets(max_pointer, MAX_READ, this->file) != NULL) {
        if (fgets(min_pointer, MIN_READ, this->file) != NULL) {
            this->cantidadRepartidores = atoi(min_pointer);

            std::string mensaje = "Configuracion: " 
                + std::string(max_pointer)
                + std::to_string(this->cantidadRepartidores) + ".\n";
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
    }
    free(max_pointer);
    free(min_pointer);
}

void Configuracion::leerArchivoDePedidos() {
    char* max_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(max_pointer, 0, MAX_READ * sizeof(char*));

    char* archivo_pointer = (char*) malloc( MAX_READ * sizeof(char*) );
    memset(archivo_pointer, 0, MAX_READ * sizeof(char*));

    // Leo el nombre del archivo de pedidos
    if (fgets(max_pointer, MAX_READ, this->file) != NULL) {

        if (fgets(archivo_pointer, MAX_READ, this->file) != NULL) {
            this->archivoDePedidos = archivo_pointer;

            std::string mensaje = "Configuracion: " 
                + std::string(max_pointer)
                + std::string(archivo_pointer) + ".\n";
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
    }
    free(max_pointer);
}


int Configuracion::getCantidadMaestrosPanaderos() {
    return this->cantidadMaestrosPanaderos;
}

int Configuracion::getCantidadRecepcionistas() {
    return this->cantidadRecepcionistas;
}

int Configuracion::getCantidadRepartidores() {
    return this->cantidadRepartidores;
}

int Configuracion::getCantidadMaestrosPizzeros() {
    return this->cantidadMaestrosPizzeros;
}

std::string Configuracion::getArchivoDePedidos() {
    return std::string(this->archivoDePedidos);
}

Configuracion::~Configuracion() {

    free(this->archivoDePedidos);
    fclose(this->file);
}