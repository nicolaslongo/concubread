#ifndef TRABAJADOR_H_
#define TRABAJADOR_H_

#include "Logger.h"

#include "SIGINT_Handler.h"
#include "SignalHandler.h"

const int PARENT_PROCESS = 0;
const int CHILD_PROCESS = 1;
const char* const PEDIDO_PAN = "Pedido de pan\n";
const char* const PEDIDO_MM = "Solicito una ración de Masa Madre al compañero Especialista\n";

class Trabajador {

    private:
        void crearHandlerParaSIGINT();
        
    protected:
        Logger* logger;
        int id;
        
        SIGINT_Handler* sigint_handler;

        int getId();

    public:

        Trabajador(Logger* logger, int myId);
        virtual ~Trabajador();
        virtual int empezarJornada() = 0;
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        bool noEsHoraDeIrse();
        virtual void abrirCanalesDeComunicacion() = 0;

};


#endif