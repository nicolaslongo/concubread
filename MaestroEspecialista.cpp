# include "MaestroEspecialista.h"

MaestroEspecialista::MaestroEspecialista (Logger* logger, int myId) : Trabajador::Trabajador(logger, myId) {
}

void MaestroEspecialista::abrirCanalesDeComunicacion() {

    try {
        fifoEscritura = new FifoEscritura(std::string("./fifos/entregas_de_MM"));
        fifoEscritura->abrir();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    try {
        fifoLectura = new FifoLectura(std::string("./fifos/pedidos_de_MM"));
        fifoLectura->abrir();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    // TODO: encapsular? No sé si esto está haciendo la diferencia!
	// SIGABRT_Handler* sigabrt_handler = new SIGABRT_Handler();
    // this->sigabrt_handler = sigabrt_handler;
	// SignalHandler :: getInstance()->registrarHandler (SIGABRT, sigabrt_handler);	

    const char* mensaje = "MaestroEspecialista: abrí los fifos <entregas_de_MM> y <pedidos_de_MM>\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();
}

int MaestroEspecialista::jornadaLaboral() {
    
    // int pid = fork();
    // if (pid != 0) {
    //     // Parent process. La Fabrica debe volver a su hilo
    //     return PARENT_PROCESS;
    // }
    // Child process. This is going to continue running from here

    // open up streams flow
    abrirCanalesDeComunicacion();

    // realizar mis tareas
    int resultado = realizarMisTareas();

    const char* msg = "Maestro especialista: Realicé mis tareas, me voy a la mierda\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}
 
int MaestroEspecialista::realizarMisTareas() {

    int iterations = 0;
    // while( this->noEsHoraDeIrseEspecialista() ) {
    while( this->noEsHoraDeIrse() ) {
        // alimentar la masa madre
        alimentarMasaMadre(masaMadre.size());

        bool hayNuevoPedido = buscarUnPedidoNuevo();

        if (hayNuevoPedido) {
            enviarRacionDeMasaMadre();
            iterations++;
        }
    }
    std::cout << "El valor de iterations es " << iterations << endl;
    return PARENT_PROCESS;
}

void MaestroEspecialista::enviarRacionDeMasaMadre() {

    int nuevaRacion = this->getRacionDeMasaMadre();
    if( !this->noEsHoraDeIrse() ) {
        return;
    }
    try {
        this->fifoEscritura->escribir( (const void*) &nuevaRacion, sizeof(int));
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
}

bool MaestroEspecialista::buscarUnPedidoNuevo() {

    char* lectura_pedido = (char*) malloc( strlen(PEDIDO_MM) * sizeof(char*) );
    memset(lectura_pedido, 0, strlen(PEDIDO_MM) * sizeof(char*));

    // if ( this->lecturaEstaPermitida() ){

    try {
        fifoLectura->lockFifo();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    try{
        this->fifoLectura->leer( (void*) lectura_pedido, strlen(PEDIDO_MM) );
    } catch( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        raise(SIGINT);
        std::cout << "Raised signal SIGINT and " << std::to_string(this->noEsHoraDeIrse()) << endl;
        return false;
        // TODO: este es el hardcodeo para que no muera!
        if (errno != 4) {
            exit(-1);
        }
    }

    try {
        fifoLectura->unlockFifo();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    if(*lectura_pedido == EOF) {
        // Tiene que andar esto eventualmente... ?
        const char* msg = "MaestroEspecialista: todos los demás maestros finalizaron de hornear. No hay más masa madre iiiiiiiiipor hoy.\n";
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
    }

    bool igualdad = (strcmp(lectura_pedido, PEDIDO_MM) == 0);
    free(lectura_pedido);
    return igualdad;
    // }
    // return false;
}

bool MaestroEspecialista::noEsHoraDeIrseEspecialista() {
    return (this->sigabrt_handler->getGracefulQuit() == 0);
}

int MaestroEspecialista::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan

    try {
        fifoEscritura->cerrar();
        fifoEscritura->eliminar();
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
        fifoLectura->eliminar();
    } catch ( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    delete fifoLectura;

    for(auto racion: masaMadre) {
        delete racion;       
    }
    return PARENT_PROCESS;
}

int MaestroEspecialista::empezarJornada() {
    return CHILD_PROCESS;
}

void MaestroEspecialista::alimentarMasaMadre(int numeroDeRacion){
    MasaMadre* racion = new MasaMadre(numeroDeRacion);
    masaMadre.push_back(racion);

    int gramaje = racion->getGramaje();
    std::string mensaje = "MaestroEspecialista: nueva ración de " + std::to_string(gramaje)
        + " gramos.\n";
    const char* msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();
}

int MaestroEspecialista::getRacionDeMasaMadre() {
    MasaMadre* estaRacion = this->masaMadre.at(this->getRacionesConsumidas());
    this->aumentarRacionesConsumidas();
    return estaRacion->getGramaje();
}

int MaestroEspecialista::getRacionesConsumidas() {
    return this->racionesConsumidas;
}

void MaestroEspecialista::aumentarRacionesConsumidas() {
    this->racionesConsumidas++;
}


// TODO: se podría llevar esto al destructor de la clase padre
MaestroEspecialista::~MaestroEspecialista() {

}
