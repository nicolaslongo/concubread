#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <stdio.h>
#include <string>
#include <string.h>

#include "Logger.h"

using namespace std;

#define CONFIG_FILE_FOLDER "config/"
const int MAX_READ = 100;
const int MIN_READ = 2;


class Configuracion {

    private:
        FILE *file;
        Logger* logger;
        int cantidadMaestrosPanaderos;
        // int cantidadMaestrosPizzeros;
        // int cantidadRecepcionistas;
        // int cantidadRepartidores;

        void leerConfigFile();

    protected:

    public:
        int getCantidadMaestrosPanaderos();
        Configuracion(Logger* logger);
        ~Configuracion();

};


#endif