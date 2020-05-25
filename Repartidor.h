#ifndef REPARTIDOR_H_
#define REPARTIDOR_H_

#include "Trabajador.h"
#include "Pipe.h"

class Repartidor : public Trabajador {

    private:

        Pipe* cajasParaEntregar;
        // Pipe* grandesCanastas;

        int buscarUnPedidoListo();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

    protected:

    public:

        Repartidor(Logger* logger, int myId, Pipe* cajasParaEntregar);
        ~Repartidor();
        int jornadaLaboral();

};


#endif