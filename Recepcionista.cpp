# include "Recepcionista.h"

Recepcionista::Recepcionista(Logger* logger, int myId, Pipe* pedidosTelefonicosDePan) : Trabajador::Trabajador(logger, myId) {

    this->pipeEscritura = pedidosTelefonicosDePan;

}

int Recepcionista::jornadaLaboral() {

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

    const char* msg_salida = "Recepcionista: realicé mis tareas, me voy a la mierda\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg_salida, strlen(msg_salida));
    this->logger->unlockLogger();

    // terminar jornada
    resultado = terminarJornada();

    return resultado;
}

void Recepcionista::abrirCanalesDeComunicacion() {

    // el Pipe ya está abierto, pero lo cierro para lectura
    this->pipeEscritura->setearModo( this->pipeEscritura->ESCRITURA );
    
    this->archivoDePedidos = new LockFile("pedidos/pedidos.txt", "r");

    const char* msg = "Recepcionista: abrí el pipe para escritura y el archivo de pedidos\n"; 
    this->logger->lockLogger();
    this->logger->writeToLogFile(msg, strlen(msg));
    this->logger->unlockLogger();

}

char* Recepcionista::atenderElTelefono() {
    char* max_pointer = (char*) malloc( TO_READ * sizeof(char*) );
    memset(max_pointer, 0, TO_READ * sizeof(char*));

    // Leo la próxima línea
    this->archivoDePedidos->tomarLock();
    char* result = fgets(max_pointer, TO_READ, this->archivoDePedidos->file );
    this->archivoDePedidos->liberarLock();

    if (result != NULL){
        // Luego hay que liberarlo!
        return max_pointer;
    }
    else {
        return NULL;
    }

}


int Recepcionista::realizarMisTareas() {
    // acá hago todo lo que tengo que hacer en un loop

    int ITERATIONS = 0;

    while( this->noEsHoraDeIrse() ) {

        if (ITERATIONS < 4) {

            char* pedido = this->atenderElTelefono();

            if (pedido != NULL) {
                
                std::string mensaje = "Recepcionista: atendí un pedido: " + std::string(pedido);
                const char* msg = mensaje.c_str();
                this->logger->lockLogger();
                this->logger->writeToLogFile(msg, strlen(msg));
                this->logger->unlockLogger();

                this->pipeEscritura->escribir( (const void*) pedido, strlen(pedido) );
                free(pedido);
                ITERATIONS++;
            }
        }
    }

    const char* exit_msg = "Recepcionista: recibí SIGINT y ya no trabajo más.\n";
    this->logger->lockLogger();
    this->logger->writeToLogFile(exit_msg, strlen(exit_msg));
    this->logger->unlockLogger();

    return CHILD_PROCESS;
}

int Recepcionista::terminarJornada() {

    // limpieza de coso
    this->pipeEscritura->cerrar();
    return CHILD_PROCESS;
}

// TODO: no lo estoy usando
int Recepcionista::empezarJornada() {
    // Este no lo estoy usando
    return CHILD_PROCESS;
}

Recepcionista::~Recepcionista() {

}

