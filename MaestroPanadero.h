#ifndef MAESTROPANADERO_H_
#define MAESTROPANADERO_H_

#include "Trabajador.h"
#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Pipe.h"

#include <unistd.h>
#include <iostream>

class MaestroPanadero : public Trabajador {

    private:
        FifoLectura* fifoLectura;
        FifoEscritura* fifoEscritura;
        Pipe* pipeLectura;

        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

    protected:

    public:
        MaestroPanadero(Logger* logger, int myId, Pipe* pipePedidosDePan);
        ~MaestroPanadero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif