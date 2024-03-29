# include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero (Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar)
                : Trabajador::Trabajador(logger, myId, listaDePedidos, pedidosTelefonicosDePan, pedidosTelefonicosDePizza,
                entregasMasaMadre, pedidosMasaMadre, cajasParaEntregar)  {
                
}

void MaestroPizzero::abrirCanalesDeComunicacion() {

    this->pedidosTelefonicosDePan->cerrar();
    this->listaDePedidos->cerrar();

    this->pedidosTelefonicosDePizza->setearModo( this->pedidosTelefonicosDePizza->LECTURA );
    this->entregasMasaMadre->setearModo( this->entregasMasaMadre->LECTURA );

    this->pedidosMasaMadre->setearModo( this->pedidosMasaMadre->ESCRITURA );
    this->cajasParaEntregar->setearModo( this->cajasParaEntregar->ESCRITURA );

    std::string std_msg = "MaestroPizzero " + std::to_string(this->getId()) + 
        ": abrí los pipes para recibir pedidos de pizza y ponerlos en cajas.\n";
    const char* mensaje = std_msg.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();

}


int MaestroPizzero::jornadaLaboral() {
    
    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }
    // Child process. This is going to continue running from here

    this->crearHandlerParaSIGINT();

    abrirCanalesDeComunicacion();

    int resultado = realizarMisTareas();
    
    resultado = terminarJornada();
    return resultado;
}

int MaestroPizzero::realizarMisTareas() {

    while( this->noEsHoraDeIrse() ) {

        bool hayNuevoPedido = buscarUnPedidoNuevo();

        if (hayNuevoPedido) {
            int* lectura_temporal = pedirNuevaRacionDeMasaMadre();
            if( !this->noEsHoraDeIrse() ){
                free(lectura_temporal);
                return CHILD_PROCESS;
            }
            int tiempoDeCoccion = hornear(*lectura_temporal);
            colocarElPedidoHorneadoEnUnaCaja(*lectura_temporal, tiempoDeCoccion);
            free(lectura_temporal);
        }
    }

    std::string mensaje = "MaestroPizzero " + std::to_string(this->getId()) +
            ": recibí SIGINT y ya no trabajo más.\n";
    const char* exit_msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();
    return CHILD_PROCESS;

}

void MaestroPizzero::colocarElPedidoHorneadoEnUnaCaja(int gramajeDeMasaMadre, int tiempoDeCoccion) {

    cajasParaEntregar->escribir( (const void*) PEDIDO_PIZZA, strlen(PEDIDO_PIZZA));

    std::string mensaje_recib =  "MaestroPizzero " + std::to_string(this->getId()) +
        ". El pedido de pizza fue horneado con " + std::to_string(gramajeDeMasaMadre) +
        " gramos de Masa Madre, y tardó " + std::to_string(tiempoDeCoccion) +
        " segundos.\n";
        
    std::cout << mensaje_recib;
    const char* recibido = mensaje_recib.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(recibido, strlen(recibido));
    this->logger->unlockLogger();

}


int MaestroPizzero::hornear(int gramajeMasaMadre) {

    int tiempoDeCoccion = definirTiempoDeCoccion( (unsigned int) gramajeMasaMadre );
    sleep(tiempoDeCoccion);
    return tiempoDeCoccion;
}

int MaestroPizzero::definirTiempoDeCoccion(unsigned int seedNumber) {

    std::srand(seedNumber * std::time(0));

    int desvio = 1 + (int) (20.0 * std::rand()/(RAND_MAX+1.0) ) + 10;

    if (desvio % 3 == 0) {
        return (TIEMPO_COCCION_ESTANDAR_PIZZA + 1);
    }
    else if (desvio % 3 == 1) {
        return (TIEMPO_COCCION_ESTANDAR_PIZZA - 1);
    }
    else {
        return (TIEMPO_COCCION_ESTANDAR_PIZZA + 0);

    }
}


int* MaestroPizzero::pedirNuevaRacionDeMasaMadre() {

    this->pedidosMasaMadre->escribir( (const void*) PEDIDO_MM, strlen(PEDIDO_MM));

    int* lectura_temporal = (int*) malloc( sizeof(int*) );
    try {
        this->entregasMasaMadre->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    this->entregasMasaMadre->leer( (void*) lectura_temporal, sizeof(int) );
    try {
        this->entregasMasaMadre->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    return lectura_temporal;

}

bool MaestroPizzero::buscarUnPedidoNuevo() {
    char* lectura_pedido = (char*) malloc( strlen(PEDIDO_PIZZA) * sizeof(char*) );
    memset(lectura_pedido, 0, strlen(PEDIDO_PIZZA) * sizeof(char*));

    try {
        this->pedidosTelefonicosDePizza->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    this->pedidosTelefonicosDePizza->leer((void*) lectura_pedido, strlen(PEDIDO_PIZZA));
    try {
        this->pedidosTelefonicosDePizza->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    bool igualdad = (strcmp(lectura_pedido, PEDIDO_PIZZA) == 0);
    free(lectura_pedido);
    return igualdad;
}

int MaestroPizzero::terminarJornada() {

    this->pedidosTelefonicosDePizza->cerrar();

    this->entregasMasaMadre->cerrar();

    this->pedidosMasaMadre->cerrar();


    return CHILD_PROCESS;
}

MaestroPizzero::~MaestroPizzero() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
