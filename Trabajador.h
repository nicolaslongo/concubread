#ifndef TRABAJADOR_H_
#define TRABAJADOR_H_

#include "FifoLectura.h"
#include "FifoEscritura.h"

const int PARENT_PROCESS = 0;
const int CHILD_PROCESS = 1;

class Trabajador {

    private:
    
    protected:

    public:

        Trabajador();
        virtual ~Trabajador() { };
        virtual int empezarJornada() = 0;
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        virtual void abrirCanalesDeComunicacion() = 0;

};


#endif