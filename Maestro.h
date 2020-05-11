#ifndef MAESTRO_H_
#define MAESTRO_H_

#include "FifoLectura.h"
#include "FifoEscritura.h"

const int PARENT_PROCESS = 0;
const int CHILD_PROCESS = 1;

class Maestro {

    private:
    
    protected:
        FifoLectura* fifoLectura;
        FifoEscritura* fifoEscritura;

    public:

        Maestro();
        virtual ~Maestro() { };
        virtual int empezarJornada() = 0;
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        virtual void abrirCanalesDeComunicacion() = 0;

};


#endif