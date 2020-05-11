#ifndef MAESTROPIZZERO_H_
#define MAESTROPIZZERO_H_

#include "Maestro.h"
#include "Logger.h"

class MaestroPizzero : public Maestro {

    private:
        
        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();

    protected:

    public:
        MaestroPizzero();
        ~MaestroPizzero();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif