#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <stdio.h>
#include <string>
#include <string.h>

#include "Logger.h"

using namespace std;

#define CONFIG_FILE_FOLDER "config/"
const int MAX_READ = 100;
const int MIN_READ = 3;


class Configuracion {

    private:
        FILE *file;
        Logger* logger;
        int cantidadMaestrosPanaderos;
        int cantidadRecepcionistas;
        // int cantidadMaestrosPizzeros;
        // int cantidadRepartidores;

        void leerConfigFile();
        void leerCantidadRecepcionistas();
        void leerCantidadMaestrosPanaderos();
    protected:

    public:
        int getCantidadMaestrosPanaderos();
        int getCantidadRecepcionistas();
        Configuracion(Logger* logger);
        ~Configuracion();

};


#endif