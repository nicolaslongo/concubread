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

    const char* msg_salida = "Recepcionista: realicé mis tareas, me voy a la mierda\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg_salida, strlen(msg_salida));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();

    return resultado;
}

void Recepcionista::abrirCanalesDeComunicacion() {

    // el Pipe ya está abierto, pero lo cierro para lectura
    this->pipeEscritura->setearModo( this->pipeEscritura->ESCRITURA );

    const char* msg = "Recepcionista: abrí el pipe para escritura\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

	SIGINT_Handler* sigint_handler = new SIGINT_Handler();
    this->sigint_handler = sigint_handler;
	SignalHandler :: getInstance()->registrarHandler (SIGINT, sigint_handler);

}

int Recepcionista::realizarMisTareas() {
    // acá hago todo lo que tengo que hacer en un loop

    int ITERATIONS = 0;

    while(this->sigint_handler->getGracefulQuit() == 0) {

        if (ITERATIONS < 4) {

            const char* PP = "Pedido de pan\n";

            this->pipeEscritura->escribir( (const void*) PP, strlen(PP) );

            const char* msg = "Recepcionista: atendí un pedido de Pan y lo pasé.\n";
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
            ITERATIONS++;
        }
    }

    const char* exit_msg = "Recepcionista: recibí SIGINT y ya no trabajo más.\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();

    return TODO_CHILD_PROCESS;
}

int Recepcionista::terminarJornada() {

    // limpieza de coso
    this->pipeEscritura->cerrar();
    delete this->sigint_handler;
    SignalHandler::destruir();
    return TODO_CHILD_PROCESS;
}

// TODO: no lo estoy usando
int Recepcionista::empezarJornada() {
    // Este no lo estoy usando
    return TODO_CHILD_PROCESS;
}

Recepcionista::~Recepcionista() {

}

