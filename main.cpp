#include "Logger.h"
#include "FabricaDePan.h"
#include "Configuracion.h"

int main() {
    // Creo el log
    Logger* logger = new Logger();
    
    Configuracion* config = new Configuracion(logger);

    // Creo la fábrica de pan y doy por comenzada la jornada laboral!
    FabricaDePan* fabrica = new FabricaDePan(logger, config);
    int resultadoDeLaJornada = fabrica->abrirLaFabrica();
    if (resultadoDeLaJornada == CHILD_PROCESS) {
        // Nada más que hacer para el Child Process
        delete fabrica;
        delete logger;
        delete config;
        return 0;
    }

    // espero a que trabajen
    sleep(10);

    // cierro la fabrica
    fabrica->cerrarLaFabrica();
    delete fabrica;
    delete logger;
    delete config;
    return 0;
}