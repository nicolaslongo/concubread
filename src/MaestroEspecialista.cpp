# include "MaestroEspecialista.h"

MaestroEspecialista::MaestroEspecialista (Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar)
                : Trabajador::Trabajador(logger, myId, listaDePedidos, pedidosTelefonicosDePan, pedidosTelefonicosDePizza,
                entregasMasaMadre, pedidosMasaMadre, cajasParaEntregar) {    

}

void MaestroEspecialista::abrirCanalesDeComunicacion() {

    this->listaDePedidos->cerrar();
    this->pedidosTelefonicosDePan->cerrar();
    this->pedidosTelefonicosDePizza->cerrar();
    this->cajasParaEntregar->cerrar();

    this->pedidosMasaMadre->setearModo( this->pedidosMasaMadre->LECTURA );
    this->entregasMasaMadre->setearModo( this->entregasMasaMadre->ESCRITURA );

    const char* mensaje = "MaestroEspecialista: abrí los fifos <entregas_de_MM> y <pedidos_de_MM>\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(mensaje, strlen(mensaje));
    this->logger->unlockLogger();
}

int MaestroEspecialista::jornadaLaboral() {
    
    this->crearHandlerParaSIGINT();

    abrirCanalesDeComunicacion();

    int resultado = realizarMisTareas();

    resultado = terminarJornada();
    return resultado;
}
 
int MaestroEspecialista::realizarMisTareas() {

    while( this->noEsHoraDeIrse() ) {

        alimentarMasaMadre(masaMadre.size());

        bool hayNuevoPedido = buscarUnPedidoNuevo();

        if (hayNuevoPedido) {
            enviarRacionDeMasaMadre();
        }
    }
    std::string mensaje = "MaestroEspecialista " + std::to_string(this->getId()) +
            ": recibí SIGINT y ya no trabajo más.\n";
    const char* exit_msg = mensaje.c_str();
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();
    return PARENT_PROCESS;
}

void MaestroEspecialista::enviarRacionDeMasaMadre() {

    int nuevaRacion = this->getRacionDeMasaMadre();
    if( !this->noEsHoraDeIrse() ) {
        return;
    }
    try {
        this->entregasMasaMadre->escribir( (const void*) &nuevaRacion, sizeof(int));
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

    try {
        this->pedidosMasaMadre->lockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }
    try{
        this->pedidosMasaMadre->leer( (void*) lectura_pedido, strlen(PEDIDO_MM) );
    } catch( std::string& mensaje ) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    try {
        this->pedidosMasaMadre->unlockPipe();
    } catch(std::string& mensaje) {
        const char* msg = mensaje.c_str();
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
        exit(-1);
    }

    if(*lectura_pedido == EOF) {
        const char* msg = "MaestroEspecialista: todos los demás maestros finalizaron de hornear. No hay más masa madre por hoy.\n";
        this->logger->lockLogger();
        this->logger->writeToLogFile(msg, strlen(msg));
        this->logger->unlockLogger();
    }

    bool igualdad = (strcmp(lectura_pedido, PEDIDO_MM) == 0);
    free(lectura_pedido);
    return igualdad;
}

int MaestroEspecialista::terminarJornada() {

    for(auto racion: masaMadre) {
        delete racion;       
    }
    return PARENT_PROCESS;
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
    estaRacion->setearConsumida();
    return estaRacion->getGramaje();
}

int MaestroEspecialista::getRacionesConsumidas() {
    return this->racionesConsumidas;
}

void MaestroEspecialista::aumentarRacionesConsumidas() {
    this->racionesConsumidas++;
}

MaestroEspecialista::~MaestroEspecialista() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}
