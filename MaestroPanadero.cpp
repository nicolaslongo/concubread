# include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero (Logger* logger, int myId) : Maestro::Maestro(myId) {
    this->logger = logger;
}

void MaestroPanadero::abrirCanalesDeComunicacion() {
    
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

    const char* mensaje = "MaestroPanadero: abrí los fifos <entregas_de_MM> y <pedidos_de_MM>\n";
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
    const char* msg = "MaestroPanadero: Realicé mis tareas, me voy a la mierda\n"; 
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
    sleep(1);
    while(iterations < 2) {

        // TODO: chequear esto try catch
        fifoEscritura->escribir( (const void*) PEDIDO_MM, strlen(PEDIDO_MM));

        // recibir la masa madre por el FIFO
        // TODO: chequear esto try catchPEDIDO_MM
        int* lectura_temporal = (int*) malloc( sizeof(int*) );

        fifoLectura->leer( (void*) lectura_temporal, sizeof(int) );

        std::cout << "Recibi esto " << *lectura_temporal << ". Soy" << this->getId() << endl;

        // hornear el pan

        // colocarlo en la gran canasta
        free(lectura_temporal);
        iterations++;
    

    }
    sleep(1);
    return CHILD_PROCESS;

}

int MaestroPanadero::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan

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
