#ifndef TRABAJADOR_H_
#define TRABAJADOR_H_

#include "Constantes.h"
#include "../utils/Logger.h"
#include "../utils/Pipe.h"
#include "../utils/SIGINT_Handler.h"
#include "../utils/SignalHandler.h"

#include <vector>

class Trabajador {

    private:
        
    protected:
        Logger* logger;
        int id;
        // std::vector<Pipe*> pipes;

        SIGINT_Handler* sigint_handler;
        int getId();

    public:

        Trabajador(Logger* logger, int myId, std::vector<Pipe*> *pipes);
        virtual ~Trabajador();
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        virtual void abrirCanalesDeComunicacion() = 0;

        void crearHandlerParaSIGINT();
        bool noEsHoraDeIrse();

};


#endif