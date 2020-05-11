#ifndef FABRICADEPAN_H_
#define FABRICADEPAN_H_

#include "MaestroPanadero.h"
#include "MaestroEspecialista.h"
#include "Logger.h"

#include <sys/wait.h>   // wait syscall
using namespace std;

class FabricaDePan {

    private:
        // 1 maestro especialista
        MaestroEspecialista* maestroEspecialista;
        // n maestros de pan
        std::vector <MaestroPanadero*> maestrosPanaderos;
        // m maestros pizzeros
        // r recepcionistas
        // d deliverys


    protected:

    public:
        FabricaDePan();
        ~FabricaDePan();
        int abrirLaFabrica();
        int cerrarLaFabrica();

};

#endif