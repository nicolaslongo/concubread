#include "Repartidor.h"

Repartidor::Repartidor(Logger* logger, int myId, Pipe* cajasParaEntregar) : 
            Trabajador::Trabajador(logger, myId) {
    
    this->cajasParaEntregar = cajasParaEntregar;
}


int Repartidor::jornadaLaboral() {
    
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

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

void Repartidor::abrirCanalesDeComunicacion() {
    this->cajasParaEntregar->setearModo( this->cajasParaEntregar->LECTURA );

    std::string std_msg = "Repartidor " + std::to_string(this->getId()) + 
        ": abrí el pipe para recibir las cajas para entregarlas\n";
    const char* mensaje = std_msg.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();
}

int Repartidor::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    while( this->noEsHoraDeIrse() ) {

        int hayUnPedidoListo = buscarUnPedidoListo();

        if (hayUnPedidoListo != PEDIDO_NULO) {

            // primero lo imprimo, luego lo escribo
            if (hayUnPedidoListo == PEDIDO_PAN_FLAG)
                std::cout << "Un pedido de pan listo" << endl;
            else if (hayUnPedidoListo == PEDIDO_PIZZA_FLAG)
                std::cout << "Un pedido de pizza listo" << endl;
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

int Repartidor::buscarUnPedidoListo() {
    
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
    this->cajasParaEntregar->leer( (void*) lectura_pedido, sizeof(int) );
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
        std::cout << "Repartidor " << std::to_string(this->getId()) << ": Leí un pedido y era NULO es esto " 
                << lectura_pedido << endl;
        free(lectura_pedido);
        return PEDIDO_NULO;
    }
}

int Repartidor::terminarJornada() {

    this->cajasParaEntregar->cerrar();

    return CHILD_PROCESS;
}

Repartidor::~Repartidor() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
