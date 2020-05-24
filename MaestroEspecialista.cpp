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
	SIGABRT_Handler* sigabrt_handler = new SIGABRT_Handler();
    this->sigabrt_handler = sigabrt_handler;
	SignalHandler :: getInstance()->registrarHandler (SIGABRT, sigabrt_handler);	

    const char* mensaje = "MaestroEspecialista: abrí los fifos <entregas_de_MM> y <pedidos_de_MM>\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();
}

int MaestroEspecialista::jornadaLaboral() {
    
    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }
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

    // bool someones_listening = true;
    int iterations = 0;
    char* lectura_temporal = (char*) malloc( strlen(PEDIDO_MM) * sizeof(char*) );
    memset(lectura_temporal, 0, strlen(PEDIDO_MM) * sizeof(char*));

    while( this->noEsHoraDeIrse() ) {
        // alimentar la masa madre
        alimentarMasaMadre(masaMadre.size());
        int gramaje = masaMadre.at(iterations)->getGramaje();
        std::string mensaje = "MaestroEspecialista: nueva ración de " + std::to_string(gramaje)
         + " gramos.\n";
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();

        this->fifoLectura->leer( (void*) lectura_temporal, strlen(PEDIDO_MM) );

        if(*lectura_temporal == EOF) {
            // Tiene que andar esto eventualmente...
            // someones_listening = false;
            const char* msg = "MaestroEspecialista: todos los demás maestros finalizaron de hornear. No hay más masa madre iiiiiiiiipor hoy.\n";
            this->logger->lockLogger();
            this->logger->writeToLogFile(msg, strlen(msg));
            this->logger->unlockLogger();
        }
        // this->logger->lockLogger();
        // this->logger->writeToLogFile(lectura_temporal, strlen(lectura_temporal));
        // this->logger->unlockLogger();

        int nuevaRacion = this->getRacionDeMasaMadre();
        if( !this->noEsHoraDeIrse() ) {
            free(lectura_temporal);
            return 0;
        }
        this->fifoEscritura->escribir( (const void*) &nuevaRacion, sizeof(int));
        iterations++;
    }
    // sleep(4);
    free(lectura_temporal);
    return 0;

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
    return CHILD_PROCESS;
}

int MaestroEspecialista::empezarJornada() {
    return CHILD_PROCESS;
}

void MaestroEspecialista::alimentarMasaMadre(int numeroDeRacion){
    MasaMadre* racion = new MasaMadre(numeroDeRacion);
    masaMadre.push_back(racion);
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
