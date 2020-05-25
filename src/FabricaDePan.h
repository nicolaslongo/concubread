#ifndef FABRICADEPAN_H_
#define FABRICADEPAN_H_

#include "MaestroEspecialista.h"
#include "MaestroPanadero.h"
#include "MaestroPizzero.h"
#include "Recepcionista.h"
#include "Repartidor.h"
// #include "Pipe.h"
#include "../utils/Logger.h"
#include "../utils/Configuracion.h"

#include <sched.h>
// #include <sys/wait.h>   // wait syscall
using namespace std;

// TODO: esto podría ser el largo de mensajes
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

        // guardo los pipes para luego liberar la memoria
        std::vector <Pipe*> pipes;

        void despacharPedidosALaListaDePedidos();

    protected:

    public:
        FabricaDePan(Logger* logger, Configuracion* config);
        ~FabricaDePan();
        int abrirLaFabrica();
        int cerrarLaFabrica();

};

#endif