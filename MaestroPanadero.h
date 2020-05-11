#ifndef MAESTROPANADERO_H_
#define MAESTROPANADERO_H_

#include "Maestro.h"
#include "Logger.h"
#include <unistd.h>

class MaestroPanadero : public Maestro {

    private:
        
        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

    protected:

    public:
        MaestroPanadero();
        ~MaestroPanadero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif