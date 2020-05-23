# include "Recepcionista.h"

Recepcionista::Recepcionista(Logger* logger, int myId, Pipe* pedidosTelefonicosDePan) : Trabajador::Trabajador() {

    this->pipeEscritura = pedidosTelefonicosDePan;
    this->logger = logger;

}

int Recepcionista::jornadaLaboral() {

    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return TODO_PARENT_PROCESS;
    }
    // Child process. This is going to continue running from here

    // open up streams flow
    abrirCanalesDeComunicacion();

    // realizar mis tareas
    int resultado = realizarMisTareas();

    const char* msg = "Recepcionista: realicé mis tareas, me voy a la mierda\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();

    return resultado;
}

void Recepcionista::abrirCanalesDeComunicacion() {

    // el Pipe ya está abierto, pero lo cierro para lectura
    this->pipeEscritura->setearModo( this->pipeEscritura->ESCRITURA );

}

int Recepcionista::realizarMisTareas() {
    // acá hago todo lo que tengo que hacer en un loop

    return TODO_CHILD_PROCESS;
}

int Recepcionista::terminarJornada() {
    // limpieza de coso

    this->pipeEscritura->cerrar();
    
    return TODO_CHILD_PROCESS;
}

// TODO: no lo estoy usando
int Recepcionista::empezarJornada() {
    // Este no lo estoy usando
    return TODO_CHILD_PROCESS;
}

Recepcionista::~Recepcionista() {

}

