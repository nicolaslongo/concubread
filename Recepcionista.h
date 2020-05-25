#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "Pipe.h"

#include <iostream>

#define PEDIDOS_FILE_FOLDER "pedidos/"

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