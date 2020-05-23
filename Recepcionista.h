#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "Pipe.h"
#include "SIGINT_Handler.h"
#include "SignalHandler.h"

class Recepcionista : public Trabajador {

    private:
        Pipe* pipeEscritura;
        Logger* logger;
        SIGINT_Handler* sigint_handler;

    protected:

    public:

        Recepcionista(Logger* logger, int myId, Pipe* pedidosTelefonicosDePan);
        ~Recepcionista();
        int empezarJornada();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif