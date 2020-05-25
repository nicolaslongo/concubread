#ifndef TRABAJADOR_H_
#define TRABAJADOR_H_

#include "Constantes.h"
#include "../utils/Logger.h"
#include "../utils/Pipe.h"
#include "../utils/SIGINT_Handler.h"
#include "../utils/SignalHandler.h"

// const int PARENT_PROCESS = 0;
// const int CHILD_PROCESS = 1;

// const int PEDIDO_NULO = 0;
// const int PEDIDO_PAN_FLAG = 1;
// const int PEDIDO_PIZZA_FLAG = 2;

// const char* const PEDIDO_PAN = "Pedido de tipo P1\n";
// const char* const PEDIDO_PIZZA = "Pedido de tipo P2\n";
// const int LARGO_PEDIDO = 18;
// const char* const PEDIDO_MM = "Solicito una ración de Masa Madre al compañero Especialista\n";

class Trabajador {

    private:
        
    protected:
        Logger* logger;
        int id;
        
        SIGINT_Handler* sigint_handler;
        int getId();

    public:

        Trabajador(Logger* logger, int myId);
        virtual ~Trabajador();
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        virtual void abrirCanalesDeComunicacion() = 0;

        void crearHandlerParaSIGINT();
        bool noEsHoraDeIrse();

};


#endif