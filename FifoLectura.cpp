#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {

}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	// TODO: cuidado con este flag O_CREAT, no vaya a ser que me haga quilombo luego
	fd = open ( nombre.c_str(), O_RDONLY );
	if(fd == -1) {
		std::string mensaje = std::string("FifoLectura:Error in open(): ") 
			+ std::string(strerror(errno));
		// Logger::writeToLogFile(mensaje);
		throw mensaje;
	}
}


ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) const {

	int resultado = read (fd, buffer, buffsize);
	if(resultado == -1) {
		std::string mensaje = std::string("FifoLectura:Error in read(): ") 
			+ std::string(strerror(errno)) + std::string("\nEste fue el fd: ")
			+ std::to_string(fd) + ". Este es errno " + std::to_string(errno);
		// Logger::writeToLogFile(mensaje);
		std::cout << mensaje << endl;
		throw mensaje;
	}
	return resultado;
}
