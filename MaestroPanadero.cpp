# include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero (Logger* logger, int myId, Pipe* pipePedidosDePan) : Maestro::Maestro(myId) {
    this->logger = logger;
    this->pipeLectura = pipePedidosDePan;
}

void MaestroPanadero::abrirCanalesDeComunicacion() {

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
    // bool keep_looping = true;
    int iterations = 0;
    while(iterations < 2) {

        char* lectura_pedido = (char*) malloc( strlen(PEDIDO_PAN) * sizeof(char*) );
        memset(lectura_pedido, 0, strlen(PEDIDO_PAN) * sizeof(char*));

        try {
            pipeLectura->lockPipe();
        } catch(std::string& mensaje) {
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
            exit(-1);
        }
        std::cout << "Estoy por leer un pedido " << endl;


        pipeLectura->leer((void*) lectura_pedido, strlen(PEDIDO_PAN));
        try {
            pipeLectura->unlockPipe();
        } catch(std::string& mensaje) {
            const char* msg = mensaje.c_str();
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
            exit(-1);
        }

        // std::string mensaje = "MaestroPanadero: recibí esto: " + std::string(lectura_pedido);
        // const char* msg = mensaje.c_str();
        // this->logger->lockLogger();
        // this->logger->writeToLogFile(msg, strlen(msg));
        // this->logger->unlockLogger();

        free(lectura_pedido);
        // Una vez que haya leído un pedido.. ahí lo pido. Antes, no
        // std::cout << "Leí un pedido " << endl;

        // TODO: chequear esto try catch
        fifoEscritura->escribir( (const void*) PEDIDO_MM, strlen(PEDIDO_MM));

        // recibir la masa madre por el FIFO
        // TODO: chequear esto try catchPEDIDO_MM
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

        std::string mensaje_recib =  "Soy MaestroPanadero " + std::to_string(this->getId()) +
            ". Tengo un pedido de pan y para ello recibí " + std::to_string(*lectura_temporal) +
            " gramos de Masa Madre, procedo a hornearlo.\n";
        std::cout << mensaje_recib;
        const char* recibido = mensaje_recib.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(recibido, strlen(recibido));
        this->logger->unlockLogger();

        // colocarlo en la gran canasta
        free(lectura_temporal);
        iterations++;

    }
    return CHILD_PROCESS;

}

int MaestroPanadero::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan

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

int MaestroPanadero::empezarJornada() {
    return CHILD_PROCESS;
}

MaestroPanadero::~MaestroPanadero() {

    
}
