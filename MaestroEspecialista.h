#ifndef MAESTROESPECIALISTA_H_
#define MAESTROESPECIALISTA_H_

#include "Maestro.h"
#include "MasaMadre.h"
#include "Logger.h"
#include <unistd.h>
#include <vector>

class MaestroEspecialista : public Maestro {

    private:
        Logger* logger;
        std::vector <MasaMadre*> masaMadre;
        int racionesConsumidas = 0;
        
        
        void crearMasaMadre();
        void alimentarMasaMadre(int numeroDeRacion);
        virtual int empezarJornada();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

    protected:

    public:
        MaestroEspecialista(Logger* logger);
        ~MaestroEspecialista();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif