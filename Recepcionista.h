#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"
#include "Pipe.h"
#include "LockFile.h"

#define PEDIDOS_FILE_FOLDER "pedidos/"
const int TO_READ = 30;

class Recepcionista : public Trabajador {

    private:
        
        Pipe* pipeEscritura;
        LockFile* archivoDePedidos;

        char* atenderElTelefono();

    protected:

    public:

        Recepcionista(Logger* logger, int myId, Pipe* pedidosTelefonicosDePan);
        ~Recepcionista();
        int empezarJornada();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif