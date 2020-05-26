#ifndef RECEPCIONISTA_H_
#define RECEPCIONISTA_H_

#include "Trabajador.h"

#include <iostream>

#define PEDIDOS_FILE_FOLDER "pedidos/"

class Recepcionista : public Trabajador {

    private:
        
        Pipe* pipeEscrituraPanes;
        Pipe* pipeEscrituraPizzas;
        Pipe* pipeLectura;
        std::vector <Pipe*> *pipes;
        
        int atenderElTelefono();

    protected:

    public:

        Recepcionista(Logger* logger, int myId, std::vector<Pipe*> *pipes);
        ~Recepcionista();
        int jornadaLaboral();
        int realizarMisTareas();
        int terminarJornada();
        void abrirCanalesDeComunicacion();

};


#endif