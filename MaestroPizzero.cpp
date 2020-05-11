# include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero () : Maestro::Maestro() {

}

int MaestroPizzero::jornadaLaboral() {
    
    // int pid = fork();
    // if (pid != 0) {
    //     // Parent process. La Fabrica debe volver a su hilo
    //     return PARENT_PROCESS;
    // }
    // Child process. This is going to continue running from here

    // realizar mis tareas
    int resultado = realizarMisTareas();
    std::string msg = "Maestro especialista: Realicé mis tareas, me voy a la mierda"; 
    Logger::writeToLogFile(msg);

    // terminar jornada
    resultado = terminarJornada();
    return resultado;
}

int MaestroPizzero::realizarMisTareas() {

    // Acá va la variable que modificaremos usando SIGNALS
    // bool keep_looping = true;
    // int iterations = 0;
    // while(iterations < 10) {
    //     // alimentar la masa madre
    //     alimentarMasaMadre(masaMadre.size());

    //     int gramaje = masaMadre.at(iterations)->getGramaje();
    //     std::string msg = "Maestro especialista: nueva ración de " + std::to_string(gramaje)
    //      + " gramos.";
    //     Logger::writeToLogFile(msg);
    //     iterations++;
    //     // escuchar pedidos de los otros Maestros
    

    //     // si los hay, otorgarles masa madre

    //     // fijarse si en el Pipe me llegó la señal de finalización. Esto es si no uso SIGNALS
    //     // sería válido???
    // }
    // sleep(2);
    return 0;

}

int MaestroPizzero::terminarJornada() {
    // Devuelvo 1 para que el proceso sepa que no soy la fabrica de pan
    return CHILD_PROCESS;
}

int MaestroPizzero::empezarJornada() {
    return CHILD_PROCESS;
}


MaestroPizzero::~MaestroPizzero() {

}
