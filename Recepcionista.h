#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "Pipe.h"

#include <iostream>

#define PEDIDOS_FILE_FOLDER "pedidos/"
const int TO_READ = 30;

const int PEDIDO_NULO = 0;
const int PEDIDO_PAN_FLAG = 1;
const int PEDIDO_PIZZA_FLAG = 2;

class Recepcionista : public Trabajador {

    private:
        
        Pipe* pipeEscrituraPanes;
        Pipe* pipeEscrituraPizzas;
        Pipe* pipeLectura;

        int atenderElTelefono();

    protected:

    public:

        Recepcionista(Logger* logger, int myId, Pipe* listaDePedidos,
                        Pipe* pedidosTelefonicosDePan, Pipe* pedidosTelefonicosDePizza);
        ~Recepcionista();
        int empezarJornada();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif