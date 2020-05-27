#ifndef MAESTROPANADERO_H_
#define MAESTROPANADERO_H_

#include "Trabajador.h"

#include <unistd.h>
#include <iostream>

const int TIEMPO_COCCION_ESTANDAR_PAN = 1;

class MaestroPanadero : public Trabajador {

    private:

        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

        bool buscarUnPedidoNuevo();
        int* pedirNuevaRacionDeMasaMadre();
        void hornear();
        void colocarElPedidoHorneadoEnUnaCaja(int gramajeDeMasaMadre);
        
    protected:

    public:
        MaestroPanadero(Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                        Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                        Pipe* cajasParaEntregar);
        ~MaestroPanadero();
        virtual int jornadaLaboral();

};


#endif