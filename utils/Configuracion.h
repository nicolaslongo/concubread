#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <stdio.h>
#include <string>
#include <string.h>

#include "Logger.h"

using namespace std;

#define CONFIG_FILE_FOLDER "config/"
const int MAX_READ = 100;
const int MIN_READ = 5;


class Configuracion {

    private:
        FILE *file;
        Logger* logger;
        int cantidadMaestrosPanaderos;
        int cantidadRecepcionistas;
        int cantidadMaestrosPizzeros;
        int cantidadRepartidores;
        char* archivoDePedidos;

        void leerConfigFile();
        void leerCantidadRecepcionistas();
        void leerCantidadMaestrosPanaderos();
        void leerCantidadMaestrosPizzeros();
        void leerCantidadRepartidores();
        void leerArchivoDePedidos();

    protected:

    public:
        int getCantidadMaestrosPanaderos();
        int getCantidadRecepcionistas();
        int getCantidadMaestrosPizzeros();
        int getCantidadRepartidores();
        std::string getArchivoDePedidos();
        Configuracion(Logger* logger);
        ~Configuracion();

};


#endif