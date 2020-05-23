#ifndef MAESTROPANADERO_H_
#define MAESTROPANADERO_H_

#include "Maestro.h"
#include "Logger.h"
#include <unistd.h>
#include <iostream>

class MaestroPanadero : public Maestro {

    private:
        Logger* logger;
        Pipe* pipeLectura;
        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

    protected:

    public:
        MaestroPanadero(Logger* logger, int myId, Pipe* pipePedidosDePan);
        ~MaestroPanadero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif