# include "MaestroEspecialista.h"

MaestroEspecialista::MaestroEspecialista () : Maestro::Maestro() {

}

void MaestroEspecialista::abrirCanalesDeComunicacion() {

    try {
        fifoEscritura = new FifoEscritura(std::string("./fifos/entregas_de_MM"));
        fifoEscritura->abrir();
        std::string mensaje = "MaestroEspecialista: abrí el fifo <entregas_de_MM>";
        Logger::writeToLogFile(mensaje);
    } catch ( std::string& mensaje ) {
        Logger::writeToLogFile(mensaje);
        exit(-1);
    }
    try {
        fifoLectura = new FifoLectura(std::string("./fifos/pedidos_de_MM"));
        fifoLectura->abrir();
        std::string mensaje = "MaestroEspecialista: abrí el fifo <pedidos_de_MM>";
        Logger::writeToLogFile(mensaje);
    } catch ( std::string& mensaje ) {
        Logger::writeToLogFile(mensaje);
        exit(-1);
    }

}

int MaestroEspecialista::jornadaLaboral() {
    
    int pid = fork();
    if (pid != 0) {
        // Parent process. La Fabrica debe volver a su hilo
        return PARENT_PROCESS;
    }
    // Child process. This is going to continue running from here
    // TODO: declare this as constants in class.h

    // open up streams flow
    abrirCanalesDeComunicacion();

    // realizar mis tareas
    int resultado = realizarMisTareas();
    std::string msg = "Maestro especialista: Realicé mis tareas, me voy a la mierda"; 
    Logger::writeToLogFile(msg);

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

int MaestroEspecialista::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    // bool keep_looping = true;
    int iterations = 0;
    while(iterations < 10) {
        // alimentar la masa madre
        alimentarMasaMadre(masaMadre.size());

        int gramaje = masaMadre.at(iterations)->getGramaje();
        std::string msg = "Maestro especialista: nueva ración de " + std::to_string(gramaje)
         + " gramos.";
        Logger::writeToLogFile(msg);
        iterations++;
        // escuchar pedidos de los otros Maestros
    

        // si los hay, otorgarles masa madre

        // fijarse si en el Pipe me llegó la señal de finalización. Esto es si no uso SIGNALS
        // sería válido???
    }
    sleep(2);
    return 0;

}

int MaestroEspecialista::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan

    try {
        fifoEscritura->cerrar();
    } catch ( std::string& mensaje ) {
        Logger::writeToLogFile(mensaje);
        exit(-1);
    }
    delete fifoEscritura;

    try {
        fifoLectura->cerrar();
    } catch ( std::string& mensaje ) {
        Logger::writeToLogFile(mensaje);
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

// TODO: se podría llevar esto al destructor de la clase padre
MaestroEspecialista::~MaestroEspecialista() {

}
