#ifndef MAESTROPIZZERO_H_
#define MAESTROPIZZERO_H_

#include "Trabajador.h"
#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Pipe.h"

#include <unistd.h>
#include <iostream>

class MaestroPizzero : public Trabajador {

    private:
        Pipe* pedidosMasaMadre;
        Pipe* entregasMasaMadre;
        Pipe* pipePedidosDePizza;

        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

        bool buscarUnPedidoNuevo();
        int* pedirNuevaRacionDeMasaMadre();
        void hornear();
        
    protected:

    public:
        MaestroPizzero(Logger* logger, int myId, Pipe* pipePedidosDePizza, Pipe* pedidosMasaMadre,
                                                Pipe* entregasMasaMadre);
        ~MaestroPizzero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif