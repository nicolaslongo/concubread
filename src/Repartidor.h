#ifndef REPARTIDOR_H_
#define REPARTIDOR_H_

#include "Trabajador.h"
#include "../utils/LockFile.h"

const std::string ENTREGADOS_FOLDER = "entregados/";

class Repartidor : public Trabajador {

    private:

        Pipe* cajasParaEntregar;
        LockFile* entregados;

        char* buscarUnPedidoListo();
        void entregarPedido(char* pedidoListo);

    protected:

    public:

        Repartidor(Logger* logger, int myId, Pipe* cajasParaEntregar);
        ~Repartidor();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif