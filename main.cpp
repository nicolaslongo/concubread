#include "Logger.h"
#include "FabricaDePan.h"

int main() {
    // Creo el log
    Logger* log = new Logger();

    // Creo la fábrica de pan y doy por comenzada la jornada laboral!
    FabricaDePan* fabrica = new FabricaDePan();
    int resultadoDeLaJornada = fabrica->abrirLaFabrica();
    if (resultadoDeLaJornada == CHILD_PROCESS) {
        // Nada más que hacer para el Child Process
        delete fabrica;
        delete log;
        return 0;
    }

    // espero a que trabajen
    sleep(10);

    // cierro la fabrica
    fabrica->cerrarLaFabrica();
    delete fabrica;
    delete log;
    return 0;
}