# include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero () : Maestro::Maestro() {
    

}

void MaestroPanadero::abrirCanalesDeComunicacion() {
    
    try {
        fifoLectura = new FifoLectura(std::string("./fifos/entregas_de_MM"));
        fifoLectura->abrir();
        std::string mensaje = "MaestroPanadero: abrí el fifo <entregas_de_MM>";
        Logger::writeToLogFile(mensaje);

    } catch ( std::string& mensaje ) {
        std::cerr << mensaje << std::endl;
        exit(-1);
    }
    try {
        fifoEscritura = new FifoEscritura(std::string("./fifos/pedidos_de_MM"));
        fifoEscritura->abrir();
        std::string mensaje = "MaestroPanadero: abrí el fifo <pedidos_de_MM>";
        Logger::writeToLogFile(mensaje);
    } catch ( std::string& mensaje ) {
        std::cerr << mensaje << std::endl;
        exit(-1);
    }

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
    std::string msg = "Maestro Panero: Realicé mis tareas, me voy a la mierda"; 
    Logger::writeToLogFile(msg);

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

int MaestroPanadero::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    // bool keep_looping = true;
    int iterations = 0;
    sleep(1);
    while(iterations < 10) {

        // pedir la masa madre por el FIFO

        // recibir la masa madre por el FIFO

        // int gramaje = masaMadre.at(iterations)->getGramaje();
        // std::string msg = "Maestro especialista: nueva ración de " + std::to_string(gramaje)
        //  + " gramos.";
        // Logger::writeToLogFile(msg);

        // hornear el pan

        // colocarlo en la gran canasta
        iterations++;
        // escuchar pedidos de los otros Maestros
    

        // si los hay, otorgarles masa madre

        // fijarse si en el Pipe me llegó la señal de finalización. Esto es si no uso SIGNALS
        // sería válido???
    }
    sleep(1);
    return 0;

}

int MaestroPanadero::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan

    try {
        fifoEscritura->cerrar();
    } catch ( std::string& mensaje ) {
        std::cerr << mensaje << std::endl;
        exit(-1);
    }
    delete fifoEscritura;

    try {
        fifoLectura->cerrar();
    } catch ( std::string& mensaje ) {
        std::cerr << mensaje << std::endl;
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
