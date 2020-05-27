# include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero (Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar)
                : Trabajador::Trabajador(logger, myId, listaDePedidos, pedidosTelefonicosDePan, pedidosTelefonicosDePizza,
                entregasMasaMadre, pedidosMasaMadre, cajasParaEntregar)  {

}

void MaestroPanadero::abrirCanalesDeComunicacion() {

    this->pedidosTelefonicosDePizza->cerrar();
    this->listaDePedidos->cerrar();

    this->pedidosTelefonicosDePan->setearModo( this->pedidosTelefonicosDePan->LECTURA );
    this->entregasMasaMadre->setearModo( this->entregasMasaMadre->LECTURA );

    this->pedidosMasaMadre->setearModo( this->pedidosMasaMadre->ESCRITURA );
    this->cajasParaEntregar->setearModo( this->cajasParaEntregar->ESCRITURA );

    std::string std_msg = "MaestroPanadero " + std::to_string(this->getId()) + 
        ": abrí los pipes para recibir pedidos de pan y ponerlos en cajas.\n";
    const char* mensaje = std_msg.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();

}


int MaestroPanadero::jornadaLaboral() {
    
    int pid = fork();
    if (pid != 0) {
        return PARENT_PROCESS;
    }

    this->crearHandlerParaSIGINT();

    abrirCanalesDeComunicacion();
    int resultado = realizarMisTareas();

    resultado = terminarJornada();
    return resultado;
}

int MaestroPanadero::realizarMisTareas() {

    while( this->noEsHoraDeIrse() ) {

        bool hayNuevoPedido = buscarUnPedidoNuevo();

        if (hayNuevoPedido) {
            int* lectura_temporal = pedirNuevaRacionDeMasaMadre();
            if( !this->noEsHoraDeIrse() ){
                free(lectura_temporal);
                return CHILD_PROCESS;
            }
            hornear();
            colocarElPedidoHorneadoEnUnaCaja(*lectura_temporal);
            free(lectura_temporal);
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

void MaestroPanadero::colocarElPedidoHorneadoEnUnaCaja(int gramajeDeMasaMadre) {

    cajasParaEntregar->escribir( (const void*) PEDIDO_PAN, strlen(PEDIDO_PAN));

    std::string mensaje_recib =  "MaestroPanadero " + std::to_string(this->getId()) +
        ". El pedido de pan fue horneado con " + std::to_string(gramajeDeMasaMadre) +
        " gramos de Masa Madre, y tardó " + std::to_string(TIEMPO_COCCION_ESTANDAR_PAN) +
        " segundo.\n";
        
    std::cout << mensaje_recib;
    const char* recibido = mensaje_recib.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(recibido, strlen(recibido));
    this->logger->unlockLogger();

}

int* MaestroPanadero::pedirNuevaRacionDeMasaMadre() {

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

    return lectura_temporal;

}

bool MaestroPanadero::buscarUnPedidoNuevo() {
    char* lectura_pedido = (char*) malloc( strlen(PEDIDO_PAN) * sizeof(char*) );
    memset(lectura_pedido, 0, strlen(PEDIDO_PAN) * sizeof(char*));

    try {
        pedidosTelefonicosDePan->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    pedidosTelefonicosDePan->leer((void*) lectura_pedido, strlen(PEDIDO_PAN));
    try {
        pedidosTelefonicosDePan->unlockPipe();
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

    this->pedidosTelefonicosDePan->cerrar();

    this->pedidosMasaMadre->cerrar();

    this->entregasMasaMadre->cerrar();

    return CHILD_PROCESS;
}

MaestroPanadero::~MaestroPanadero() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
