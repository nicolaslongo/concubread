# include "Recepcionista.h"

Recepcionista::Recepcionista(Logger* logger, int myId, Pipe* listaDePedidos,
                Pipe* pedidosTelefonicosDePan, Pipe* pedidosTelefonicosDePizza) : Trabajador::Trabajador(logger, myId) {

    this->pipeLectura = listaDePedidos;
    this->pipeEscrituraPanes = pedidosTelefonicosDePan;
    this->pipeEscrituraPizzas = pedidosTelefonicosDePizza;

}

int Recepcionista::jornadaLaboral() {

    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }

    // Child process. This is going to continue running from here
    this->crearHandlerParaSIGINT();
    
    // open up streams flow
    abrirCanalesDeComunicacion();

    // realizar mis tareas
    int resultado = realizarMisTareas();

    // terminar jornada
    resultado = terminarJornada();

    return resultado;
}

void Recepcionista::abrirCanalesDeComunicacion() {

    // el Pipe ya está abierto, pero lo cierro para lectura
    this->pipeEscrituraPanes->setearModo( this->pipeEscrituraPanes->ESCRITURA );
    this->pipeEscrituraPizzas->setearModo( this->pipeEscrituraPizzas->ESCRITURA );
    this->pipeLectura->setearModo( this->pipeLectura->LECTURA );
    
    std::string mensaje = "Recepcionista " + std::to_string(this->getId()) + 
        ": abrí el pipe para escritura y lectura\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

}

int Recepcionista::atenderElTelefono() {

    char* lectura_pedido = (char*) malloc( LARGO_PEDIDO * sizeof(char*) );
    memset(lectura_pedido, 0, LARGO_PEDIDO * sizeof(char*));

    try {
        pipeLectura->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    pipeLectura->leer((void*) lectura_pedido, LARGO_PEDIDO);
    try {
        pipeLectura->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    if(strcmp(lectura_pedido, PEDIDO_PAN) == 0) {
        // std::cout << "Recepcionista " << std::to_string(this->getId()) << ": Leí un pedido y era de panes" << endl;
        free(lectura_pedido);
        return PEDIDO_PAN_FLAG;
    }
    else if( strcmp(lectura_pedido, PEDIDO_PIZZA) == 0) {
        // std::cout << "Recepcionista " << std::to_string(this->getId()) << ": Leí un pedido y era de pizzas" << endl;
        free(lectura_pedido);
        return PEDIDO_PIZZA_FLAG;
    }
    else {
        free(lectura_pedido);
        return PEDIDO_NULO;
    }
}


int Recepcionista::realizarMisTareas() {
    // acá hago todo lo que tengo que hacer en un loop

    while( this->noEsHoraDeIrse() ) {

        int pedido = this->atenderElTelefono();

        if (pedido != PEDIDO_NULO) {
            Pipe* pipe;
            const char* pedido_str;
            if (pedido == PEDIDO_PAN_FLAG){
                pipe = this->pipeEscrituraPanes;
                pedido_str = PEDIDO_PAN;
            }
            else if (pedido == PEDIDO_PIZZA_FLAG) {
                pipe = this->pipeEscrituraPizzas;
                pedido_str = PEDIDO_PIZZA;
            }

            std::string mensaje = "Recepcionista " + std::to_string(this->getId()) + 
                ": atendí un pedido " + std::string(pedido_str);
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();

            pipe->escribir( (const void*) pedido_str, strlen(pedido_str) );
        }
    }

    std::string mensaje = "Recepcionista " + std::to_string(this->getId()) +
            ": recibí SIGINT y ya no trabajo más.\n";
    const char* exit_msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();
    return CHILD_PROCESS;
}

int Recepcionista::terminarJornada() {

    // limpieza de coso
    this->pipeEscrituraPanes->cerrar();
    this->pipeEscrituraPizzas->cerrar();
    this->pipeLectura->cerrar();
    return CHILD_PROCESS;
}

// TODO: no lo estoy usando
int Recepcionista::empezarJornada() {
    // Este no lo estoy usando
    return CHILD_PROCESS;
}

Recepcionista::~Recepcionista() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}

