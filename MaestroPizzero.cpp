# include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero (Logger* logger, int myId, Pipe* pipePedidosDePizza) : Trabajador::Trabajador(logger, myId) {
    this->pipeLectura = pipePedidosDePizza;
}

void MaestroPizzero::abrirCanalesDeComunicacion() {

    this->pipeLectura->setearModo( this->pipeLectura->LECTURA );
    
    try {
        fifoLectura = new FifoLectura(std::string("./fifos/entregas_de_MM"));
        fifoLectura->abrir();

    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    try {
        fifoEscritura = new FifoEscritura(std::string("./fifos/pedidos_de_MM"));
        fifoEscritura->abrir();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    std::string std_msg = "MaestroPizzero " + std::to_string(this->getId()) + 
        ": abrí los fifos <entregas_de_MM> y <pedidos_de_MM> y también el Pipe para recibir pedidos de pizza\n";
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
    abrirCanalesDeComunicacion();
    // realizar mis tareas
    int resultado = realizarMisTareas();
    std::string std_msg = "MaestroPizzero " + std::to_string(this->getId()) + 
        ": Realicé mis tareas, me voy a la mierda\n";
    const char* msg = std_msg.c_str(); 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

int MaestroPizzero::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    int iterations = 0;
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
        iterations++;
    }
    return CHILD_PROCESS;

}

void MaestroPizzero::hornear() {
    sleep(2);
}

int* MaestroPizzero::pedirNuevaRacionDeMasaMadre() {

    // TODO: chequear esto try catch
    fifoEscritura->escribir( (const void*) PEDIDO_MM, strlen(PEDIDO_MM));

    int* lectura_temporal = (int*) malloc( sizeof(int*) );
    try {
        fifoLectura->lockFifo();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    fifoLectura->leer( (void*) lectura_temporal, sizeof(int) );
    try {
        fifoLectura->unlockFifo();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    std::string mensaje_recib =  "Soy MaestroPizzero " + std::to_string(this->getId()) +
        ". Tengo un pedido de pizza y para ello recibí " + std::to_string(*lectura_temporal) +
        " gramos de Masa Madre, procedo a hornearlo.\n";
    std::cout << mensaje_recib;
    const char* recibido = mensaje_recib.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(recibido, strlen(recibido));
    this->logger->unlockLogger();
    return lectura_temporal;

}

bool MaestroPizzero::buscarUnPedidoNuevo() {
    char* lectura_pedido = (char*) malloc( strlen(PEDIDO_PIZZA) * sizeof(char*) );
    memset(lectura_pedido, 0, strlen(PEDIDO_PIZZA) * sizeof(char*));

    try {
        pipeLectura->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    pipeLectura->leer((void*) lectura_pedido, strlen(PEDIDO_PIZZA));
    try {
        pipeLectura->unlockPipe();
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

    this->pipeLectura->cerrar();

    try {
        fifoEscritura->cerrar();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    delete fifoEscritura;

    try {
        fifoLectura->cerrar();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    delete fifoLectura;

    return CHILD_PROCESS;
}

// TODO: borrar this right now
int MaestroPizzero::empezarJornada() {
    return CHILD_PROCESS;
}

MaestroPizzero::~MaestroPizzero() {

    
}
