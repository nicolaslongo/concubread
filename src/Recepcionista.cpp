# include "Recepcionista.h"

Recepcionista::Recepcionista(Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar) : Trabajador::Trabajador(logger, myId, listaDePedidos,
                pedidosTelefonicosDePan, pedidosTelefonicosDePizza, entregasMasaMadre, pedidosMasaMadre,
                cajasParaEntregar) {

}

int Recepcionista::jornadaLaboral() {

    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }

    this->crearHandlerParaSIGINT();
    
    abrirCanalesDeComunicacion();

    int resultado = realizarMisTareas();

    resultado = terminarJornada();

    return resultado;
}

void Recepcionista::abrirCanalesDeComunicacion() {

    this->cajasParaEntregar->cerrar();
    this->pedidosMasaMadre->cerrar();
    this->entregasMasaMadre->cerrar();

    this->pedidosTelefonicosDePan->setearModo( this->pedidosTelefonicosDePan->ESCRITURA );
    this->pedidosTelefonicosDePizza->setearModo( this->pedidosTelefonicosDePizza->ESCRITURA );
    this->listaDePedidos->setearModo( this->listaDePedidos->LECTURA );
    
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
        listaDePedidos->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    listaDePedidos->leer((void*) lectura_pedido, LARGO_PEDIDO);
    try {
        listaDePedidos->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    if(strcmp(lectura_pedido, PEDIDO_PAN) == 0) {
        free(lectura_pedido);
        return PEDIDO_PAN_FLAG;
    }
    else if( strcmp(lectura_pedido, PEDIDO_PIZZA) == 0) {
        free(lectura_pedido);
        return PEDIDO_PIZZA_FLAG;
    }
    else {
        // TODO: borrar iostream
        // std::cout << "Recepcionista " << std::to_string(this->getId()) << ": Leí un pedido y no sé qué era " 
        //         << lectura_pedido << endl;
        free(lectura_pedido);
        return PEDIDO_NULO;
    }
}


int Recepcionista::realizarMisTareas() {

    while( this->noEsHoraDeIrse() ) {

        int pedido = this->atenderElTelefono();

        if (pedido != PEDIDO_NULO) {
            Pipe* pipe;
            const char* pedido_str;
            if (pedido == PEDIDO_PAN_FLAG){
                pipe = this->pedidosTelefonicosDePan;
                pedido_str = PEDIDO_PAN;
            }
            else if (pedido == PEDIDO_PIZZA_FLAG) {
                pipe = this->pedidosTelefonicosDePizza;
                pedido_str = PEDIDO_PIZZA;
            }

            std::string mensaje = "Recepcionista " + std::to_string(this->getId()) + 
                ": atendí un " + std::string(pedido_str);
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

    this->pedidosTelefonicosDePan->cerrar();
    this->pedidosTelefonicosDePizza->cerrar();
    this->listaDePedidos->cerrar();
    return CHILD_PROCESS;
}


Recepcionista::~Recepcionista() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}

