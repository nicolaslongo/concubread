#ifndef MAESTRO_H_
#define MAESTRO_H_

#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Pipe.h"

const int PARENT_PROCESS = 0;
const int CHILD_PROCESS = 1;
const char* const PEDIDO_PAN = "Pedido de pan\n";
const char* const PEDIDO_MM = "Solicito una ración de Masa Madre al compañero Especialista\n";

class Maestro {

    private:
    
    protected:
        int id;
        FifoLectura* fifoLectura;
        FifoEscritura* fifoEscritura;
        int getId();

    public:

        Maestro(int myId);
        virtual ~Maestro() { };
        virtual int empezarJornada() = 0;
        virtual int jornadaLaboral() = 0;
        virtual int realizarMisTareas() = 0;
        virtual int terminarJornada() = 0;
        virtual void abrirCanalesDeComunicacion() = 0;

};


#endif