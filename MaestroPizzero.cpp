# include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero (Logger* logger, int myId, Pipe* pipePedidosDePizza,
            Pipe* pipePedidosMasaMadre, Pipe* pipeEntregasMasaMadre) : Trabajador::Trabajador(logger, myId) {

    this->pipePedidosDePizza = pipePedidosDePizza;
    this->pedidosMasaMadre = pipePedidosMasaMadre;
    this->entregasMasaMadre = pipeEntregasMasaMadre;
}

void MaestroPizzero::abrirCanalesDeComunicacion() {

    this->pipePedidosDePizza->setearModo( this->pipePedidosDePizza->LECTURA );
    this->entregasMasaMadre->setearModo( this->entregasMasaMadre->LECTURA );
    this->pedidosMasaMadre->setearModo( this->pedidosMasaMadre->ESCRITURA );


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

    this->crearHandlerParaSIGINT();

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
        this->pipePedidosDePizza->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    this->pipePedidosDePizza->leer((void*) lectura_pedido, strlen(PEDIDO_PIZZA));
    try {
        this->pipePedidosDePizza->unlockPipe();
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

    this->pipePedidosDePizza->cerrar();
    // delete this->pipePedidosDePizza;
    this->entregasMasaMadre->cerrar();
    // delete this->entregasMasaMadre;
    this->pedidosMasaMadre->cerrar();
    // delete this->pedidosMasaMadre;

    return CHILD_PROCESS;
}

// TODO: borrar this right now
int MaestroPizzero::empezarJornada() {
    return CHILD_PROCESS;
}

MaestroPizzero::~MaestroPizzero() {

    
}
