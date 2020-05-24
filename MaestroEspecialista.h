#ifndef MAESTROESPECIALISTA_H_
#define MAESTROESPECIALISTA_H_

#include "Trabajador.h"
#include "Pipe.h"
#include "MasaMadre.h"

#include <iostream>
#include <unistd.h>
#include <vector>

class MaestroEspecialista : public Trabajador {

    private:

        Pipe* pedidosMasaMadre;
        Pipe* entregasMasaMadre;

        std::vector <MasaMadre*> masaMadre;
        int racionesConsumidas = 0;
        
        
        void crearMasaMadre();
        void alimentarMasaMadre(int numeroDeRacion);
        int getRacionDeMasaMadre();
        int getRacionesConsumidas();
        void aumentarRacionesConsumidas();
        virtual int realizarMisTareas();
        virtual int terminarJornada();
        virtual void abrirCanalesDeComunicacion();

        bool noEsHoraDeIrseEspecialista();
        bool buscarUnPedidoNuevo();
        void enviarRacionDeMasaMadre();

    protected:

    public:
        MaestroEspecialista(Logger* logger, int myId, Pipe* pedidosMasaMadre, Pipe* entregasMasaMadre);
        ~MaestroEspecialista();
        virtual int jornadaLaboral();       // capaz este esté de más

};


#endif