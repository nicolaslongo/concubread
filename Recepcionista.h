#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "FifoLectura.h"
#include "FifoEscritura.h"

class Recepcionista : public Trabajador {

    private:
        FifoEscritura* fifoEscritura;

    protected:

    public:

        Recepcionista();
        ~Recepcionista();
        int empezarJornada();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif