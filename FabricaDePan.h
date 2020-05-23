#ifndef FABRICADEPAN_H_
#define FABRICADEPAN_H_

#include "Pedido.h"
#include "MaestroPanadero.h"
#include "MaestroEspecialista.h"
#include "Logger.h"
#include "Configuracion.h"

#include <sched.h>
#include <sys/wait.h>   // wait syscall
using namespace std;

class FabricaDePan {

    private:
        Logger* logger;
        Configuracion* config;
        // 1 maestro especialista
        MaestroEspecialista* maestroEspecialista;
        // n maestros de pan
        std::vector <MaestroPanadero*> maestrosPanaderos;
        // m maestros pizzeros
        // r recepcionistas
        // d deliverys

    protected:

    public:
        std::vector<Pedido> pedidos;
        FabricaDePan(Logger* logger, Configuracion* config);
        ~FabricaDePan();
        int abrirLaFabrica();
        int cerrarLaFabrica();

};

#endif