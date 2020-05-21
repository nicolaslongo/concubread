# include "Recepcionista.h"

Recepcionista::Recepcionista() : Trabajador::Trabajador() {

}

int Recepcionista::jornadaLaboral() {
    // Acá hago el fork

    return CHILD_PROCESS;
}

void Recepcionista::abrirCanalesDeComunicacion() {
    // abro los Fifos    
}

int Recepcionista::realizarMisTareas() {
    // acá hago todo lo que tengo que hacer en un loop

    return CHILD_PROCESS;
}

int Recepcionista::terminarJornada() {
    // limpieza de coso
    
    return CHILD_PROCESS;
}

// TODO: no lo estoy usando
int Recepcionista::empezarJornada() {
    // Este no lo estoy usando
    return CHILD_PROCESS;
}

Recepcionista::~Recepcionista() {

}

