# include "Trabajador.h"

Trabajador::Trabajador(Logger* logger, int myId, Pipe* listaDePedidos, Pipe* pedidosTelefonicosDePan,
                Pipe* pedidosTelefonicosDePizza, Pipe* entregasMasaMadre, Pipe* pedidosMasaMadre,
                Pipe* cajasParaEntregar) {
    this->logger = logger;
    this->id = myId;

    this->pedidosMasaMadre = pedidosMasaMadre;
    this->entregasMasaMadre = entregasMasaMadre;
    this->listaDePedidos = listaDePedidos;
    this->pedidosTelefonicosDePan = pedidosTelefonicosDePan;
    this->pedidosTelefonicosDePizza = pedidosTelefonicosDePizza;
    this->cajasParaEntregar = cajasParaEntregar;

    this->sigint_handler = NULL;
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
}