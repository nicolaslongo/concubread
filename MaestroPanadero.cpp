# include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero (Logger* logger, int myId, Pipe* pipePedidosDePan,
            Pipe* pipePedidosMasaMadre, Pipe* pipeEntregasMasaMadre) : Trabajador::Trabajador(logger, myId) {

    this->pipePedidosDePan = pipePedidosDePan;
    this->pedidosMasaMadre = pipePedidosMasaMadre;
    this->entregasMasaMadre = pipeEntregasMasaMadre;
}

void MaestroPanadero::abrirCanalesDeComunicacion() {

    this->pipePedidosDePan->setearModo( this->pipePedidosDePan->LECTURA );
    this->entregasMasaMadre->setearModo( this->entregasMasaMadre->LECTURA );

    this->pedidosMasaMadre->setearModo( this->pedidosMasaMadre->ESCRITURA );

    std::string std_msg = "MaestroPanadero " + std::to_string(this->getId()) + 
        ": abrí los fifos <entregas_de_MM> y <pedidos_de_MM> y también el Pipe para recibir pedidos de pan\n";
    const char* mensaje = std_msg.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();

}


int MaestroPanadero::jornadaLaboral() {
    
    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }

    this->crearHandlerParaSIGINT();

    // Child process. This is going to continue running from here
    abrirCanalesDeComunicacion();
    // realizar mis tareas
    int resultado = realizarMisTareas();
    std::string std_msg = "MaestroPanadero " + std::to_string(this->getId()) + 
        ": Realicé mis tareas, me voy a la mierda\n";
    const char* msg = std_msg.c_str(); 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

int MaestroPanadero::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    while( this->noEsHoraDeIrse() ) {

        bool hayNuevoPedido = buscarUnPedidoNuevo();

        if (hayNuevoPedido) {
            int* lectura_temporal = pedirNuevaRacionDeMasaMadre();
            if( !this->noEsHoraDeIrse() ){
                free(lectura_temporal);
                return CHILD_PROCESS;
            }
            free(lectura_temporal);
            hornear();
            //colocar en la gran canasta
        }
    }

    std::string mensaje = "MaestroPanadero " + std::to_string(this->getId()) +
            ": recibí SIGINT y ya no trabajo más.\n";
    const char* exit_msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();
    return CHILD_PROCESS;

}

void MaestroPanadero::hornear() {
    sleep(TIEMPO_COCCION_ESTANDAR_PAN);
}

int* MaestroPanadero::pedirNuevaRacionDeMasaMadre() {

    // TODO: chequear esto try catch
    pedidosMasaMadre->escribir( (const void*) PEDIDO_MM, strlen(PEDIDO_MM));

    int* lectura_temporal = (int*) malloc( sizeof(int*) );
    try {
        entregasMasaMadre->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    entregasMasaMadre->leer( (void*) lectura_temporal, sizeof(int) );
    try {
        entregasMasaMadre->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    std::string mensaje_recib =  "MaestroPanadero " + std::to_string(this->getId()) +
        ". Tengo un pedido de pan y para ello recibí " + std::to_string(*lectura_temporal) +
        " gramos de Masa Madre, procedo a hornearlo.\n";
    std::cout << mensaje_recib;
    const char* recibido = mensaje_recib.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(recibido, strlen(recibido));
    this->logger->unlockLogger();
    return lectura_temporal;

}

bool MaestroPanadero::buscarUnPedidoNuevo() {
    char* lectura_pedido = (char*) malloc( strlen(PEDIDO_PAN) * sizeof(char*) );
    memset(lectura_pedido, 0, strlen(PEDIDO_PAN) * sizeof(char*));

    try {
        pipePedidosDePan->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    pipePedidosDePan->leer((void*) lectura_pedido, strlen(PEDIDO_PAN));
    try {
        pipePedidosDePan->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    bool igualdad = (strcmp(lectura_pedido, PEDIDO_PAN) == 0);
    free(lectura_pedido);
    return igualdad;
}

int MaestroPanadero::terminarJornada() {

    this->pipePedidosDePan->cerrar();

    this->pedidosMasaMadre->cerrar();

    this->entregasMasaMadre->cerrar();

    return CHILD_PROCESS;
}

MaestroPanadero::~MaestroPanadero() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
