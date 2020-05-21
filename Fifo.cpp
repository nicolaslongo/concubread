#include "Fifo.h"

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
	int resultado = close ( fd );
	if(resultado == -1) {
		std::string mensaje = std::string("Fifo:Error in close(): ") 
			+ std::string(strerror(errno)) + std::string("\nEste fue el fd: ")
			+ std::to_string(fd);
		// Logger::writeToLogFile(mensaje);
		throw mensaje;
	}
	fd = -1;
}

void Fifo::eliminar() const {
	unlink ( nombre.c_str() );
}
