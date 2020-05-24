#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "Pipe.h"

class Recepcionista : public Trabajador {

    private:
        
        Pipe* pipeEscritura;

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