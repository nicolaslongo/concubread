#ifndef MAESTROPIZZERO_H_
#define MAESTROPIZZERO_H_

#include "Trabajador.h"
#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Pipe.h"

#include <unistd.h>
#include <iostream>

const int TIEMPO_COCCION_ESTANDAR_PIZZA = 2;

class MaestroPizzero : public Trabajador {

    private:
        Pipe* pedidosMasaMadre;
        Pipe* entregasMasaMadre;
        Pipe* pipePedidosDePizza;
        Pipe* cajasParaEntregar;

        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

        bool buscarUnPedidoNuevo();
        int* pedirNuevaRacionDeMasaMadre();
        void hornear(int gramajeMasaMadre);
        int definirTiempoDeCoccion(unsigned int seedNumber);
        
    protected:

    public:
        MaestroPizzero(Logger* logger, int myId, Pipe* pipePedidosDePizza, Pipe* pedidosMasaMadre,
                                                Pipe* entregasMasaMadre, Pipe* cajasParaEntregar);
        ~MaestroPizzero();
        virtual int jornadaLaboral();

};


#endif