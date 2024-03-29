#include "./utils/Logger.h"
#include "./src/FabricaDePan.h"
#include "./utils/Configuracion.h"

int main() {
    Logger* logger = new Logger();
    
    Configuracion* config = new Configuracion(logger);

    // Creo la fábrica de pan y doy por comenzada la jornada laboral
    FabricaDePan* fabrica = new FabricaDePan(logger, config);
    int resultadoDeLaJornada = fabrica->abrirLaFabrica();
    if (resultadoDeLaJornada == CHILD_PROCESS) {
        
        // Nada más que hacer para el Child Process
        delete fabrica;
        delete logger;
        delete config;
        return 0;
    }

    fabrica->cerrarLaFabrica();
    delete fabrica;
    delete logger;
    delete config;
    return 0;
}