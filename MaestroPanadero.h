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
        Pipe* pedidosMasaMadre;
        Pipe* entregasMasaMadre;
        Pipe* pipePedidosDePan;

        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

        bool buscarUnPedidoNuevo();
        int* pedirNuevaRacionDeMasaMadre();
        void hornear();
        
    protected:

    public:
        MaestroPanadero(Logger* logger, int myId, Pipe* pipePedidosDePan, Pipe* pedidosMasaMadre,
                                                Pipe* entregasMasaMadre);
        ~MaestroPanadero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif