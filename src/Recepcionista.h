#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"

#define PEDIDOS_FILE_FOLDER "pedidos/"

class Recepcionista : public Trabajador {

    private:
        
        int atenderElTelefono();

    protected:

    public:

        Recepcionista(Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                            Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                            Pipe* cajasParaEntregar);
        ~Recepcionista();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif