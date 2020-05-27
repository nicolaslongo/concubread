#include "Repartidor.h"

Repartidor::Repartidor(Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar) : Trabajador::Trabajador(logger, myId, listaDePedidos,
                pedidosTelefonicosDePan, pedidosTelefonicosDePizza, entregasMasaMadre, pedidosMasaMadre,
                cajasParaEntregar) {
    
}

int Repartidor::jornadaLaboral() {
    
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

void Repartidor::abrirCanalesDeComunicacion() {
    
    this->pedidosMasaMadre->cerrar();
    this->entregasMasaMadre->cerrar();
    this->pedidosTelefonicosDePan->cerrar();
    this->pedidosTelefonicosDePizza->cerrar();
    this->listaDePedidos->cerrar();


    this->cajasParaEntregar->setearModo( this->cajasParaEntregar->LECTURA );

    const std::string nombre = ENTREGADOS_FOLDER + "entregados.txt";
    this->entregados = new LockFile( nombre );

    std::string std_msg = "Repartidor " + std::to_string(this->getId()) + 
        ": abrí el pipe para recibir las cajas para entregarlas\n";
    const char* mensaje = std_msg.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();
}

int Repartidor::realizarMisTareas() {

    while( this->noEsHoraDeIrse() ) {

        char* pedido = buscarUnPedidoListo();
        if (pedido != NULL) {
            entregarPedido(pedido);
            free(pedido);
        }
    }

    std::string mensaje = "Repartidor " + std::to_string(this->getId()) +
            ": recibí SIGINT y ya no trabajo más.\n";
    const char* exit_msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();

    return CHILD_PROCESS;
}

void Repartidor::entregarPedido(char* pedido) {

    entregados->tomarLock();
    entregados->escribir( pedido, strlen(pedido) );
    entregados->liberarLock();

}

char* Repartidor::buscarUnPedidoListo() {
    
    char* lectura_pedido = (char*) malloc( LARGO_PEDIDO * sizeof(char*) );
    memset(lectura_pedido, 0, LARGO_PEDIDO * sizeof(char*));

    try {
        this->cajasParaEntregar->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    this->cajasParaEntregar->leer( (void*) lectura_pedido, LARGO_PEDIDO );
    try {
        this->cajasParaEntregar->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    if(strcmp(lectura_pedido, PEDIDO_PAN) == 0) {
        return lectura_pedido;
    }
    else if( strcmp(lectura_pedido, PEDIDO_PIZZA) == 0) {
        return lectura_pedido;
    }
    else {
        free(lectura_pedido);
        return NULL;
    }
}

int Repartidor::terminarJornada() {

    this->cajasParaEntregar->cerrar();
    delete this->entregados;
    return CHILD_PROCESS;
}

Repartidor::~Repartidor() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
