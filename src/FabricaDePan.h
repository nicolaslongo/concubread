#ifndef FABRICADEPAN_H_
#define FABRICADEPAN_H_

#include "MaestroEspecialista.h"
#include "MaestroPanadero.h"
#include "MaestroPizzero.h"
#include "Recepcionista.h"
#include "Repartidor.h"
#include "../utils/Logger.h"
#include "../utils/Configuracion.h"

#include <algorithm> // for copy() and assign() 
#include <iterator> // for back_inserter
#include <sched.h>
using namespace std;

const int TO_READ = 30;

class FabricaDePan {

    private:
        Logger* logger;
        Pipe* listaDePedidos;
        Configuracion* config;

        // 1 maestro especialista
        MaestroEspecialista* maestroEspecialista;

        // n maestros de pan
        std::vector <MaestroPanadero*> maestrosPanaderos;

        // m maestros pizzeros
        std::vector <MaestroPizzero*> maestrosPizzeros;

        // r recepcionistas
        std::vector <Recepcionista*> recepcionistas;

        // d repartidores
        std::vector <Repartidor*> repartidores;

        std::vector <Pipe*> pipes;

        void abrirLaLineaTelefonicaParaPedidos();

    protected:

    public:
        FabricaDePan(Logger* logger, Configuracion* config);
        ~FabricaDePan();
        int abrirLaFabrica();
        int cerrarLaFabrica();

};

#endif