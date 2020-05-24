# include "Trabajador.h"

Trabajador::Trabajador(Logger* logger, int myId) {
    this->logger = logger;
    this->id = myId;
}

void Trabajador::crearHandlerParaSIGINT() {
	SIGINT_Handler* sigint_handler = new SIGINT_Handler();
    this->sigint_handler = sigint_handler;
	SignalHandler :: getInstance()->registrarHandler (SIGINT, sigint_handler);	
}

bool Trabajador::noEsHoraDeIrse() {
    return (this->sigint_handler->getGracefulQuit() == 0);
}

int Trabajador::getId() {
    return this->id;
}

Trabajador::~Trabajador() {
    delete this->sigint_handler;
    SignalHandler::destruir();
}