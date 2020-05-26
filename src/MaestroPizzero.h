#ifndef MAESTROPIZZERO_H_
#define MAESTROPIZZERO_H_

#include "Trabajador.h"

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
        int hornear(int gramajeMasaMadre);
        int definirTiempoDeCoccion(unsigned int seedNumber);
        void colocarElPedidoHorneadoEnUnaCaja(int gramajeDeMasaMadre, int tiempoDeCoccion);

    protected:

    public:
        MaestroPizzero(Logger* logger, int myId, std::vector<Pipe*> *pipes);
        ~MaestroPizzero();
        virtual int jornadaLaboral();

};


#endif