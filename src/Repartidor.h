#ifndef REPARTIDOR_H_
#define REPARTIDOR_H_

#include "Trabajador.h"
#include "../utils/LockFile.h"

const std::string ENTREGADOS_FOLDER = "entregados/";

class Repartidor : public Trabajador {

    private:

        Pipe* cajasParaEntregar;
        LockFile* entregados;
        std::vector <Pipe*> *pipes;
        
        char* buscarUnPedidoListo();
        void entregarPedido(char* pedidoListo);

    protected:

    public:

        Repartidor(Logger* logger, int myId, std::vector<Pipe*> *pipes);
        ~Repartidor();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif