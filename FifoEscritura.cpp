#include "FifoEscritura.h"

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {

}

FifoEscritura::~FifoEscritura() {

}

void FifoEscritura::abrir() {
	// TODO: cuidado con este flag O_CREAT, no vaya a ser que me haga quilombo luego
	fd = open ( nombre.c_str(), O_WRONLY );
	
	if(fd == -1) {
		std::string mensaje = std::string("FifoEscritura:Error in open(): ") 
			+ std::string(strerror(errno));
		// Logger::writeToLogFile(mensaje);
		throw mensaje;
	}
	// Logger::writeToLogFile(std::string("FifoEscritura: fd resultado es ") + std::to_string(fd));
}

ssize_t FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const {	
	int resultado = write ( fd,buffer,buffsize );
	if(resultado == -1) {
		std::string mensaje = std::string("FifoEscritura:Error in write(): ") 
			+ std::string(strerror(errno)) + std::string("\nEste fue el fd: ")
			+ std::to_string(fd);
		// Logger::writeToLogFile(mensaje);
		throw mensaje;
	}
	return resultado;
}
