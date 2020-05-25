#include "Pipe.h"

Pipe :: Pipe() : lectura(true), escritura(true) {
	pipe ( this->descriptores );
}

Pipe::~Pipe() {
}

void Pipe :: setearModo ( const int modo ) {
	if ( modo == LECTURA ) {
		close ( this->descriptores[1] );
		this->escritura = false;

	} else if ( modo == ESCRITURA ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}
}

ssize_t Pipe :: escribir ( const void* dato,int datoSize ) {
	if ( this->lectura == true ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}

	return write ( this->descriptores[1],dato,datoSize );
}

ssize_t Pipe :: leer ( void* buffer,const int buffSize ) {
	if ( this->escritura == true ) {
		close ( this->descriptores[1] );
		this->escritura = false;
	}

	return read ( this->descriptores[0],buffer,buffSize );
}

int Pipe::lockPipe() {
	int fd;
	if (this->lectura == true) {
		fd = this->descriptores[LECTURA];
	}
	else if (this->escritura == true) {
		fd = this->descriptores[ESCRITURA];
	}

	int resultado_lock = flock(fd, LOCK_EX);
	if (resultado_lock == -1) {
		throw "Error lockeando un Pipe. Este es mi fd " + std::to_string(fd);
	}
	return resultado_lock;
}

int Pipe::unlockPipe() {
	int fd;
	if (this->lectura == true) {
		fd = this->descriptores[LECTURA];
	}
	else if (this->escritura == true) {
		fd = this->descriptores[ESCRITURA];
	}
	int resultado_lock = flock( fd, LOCK_UN);
	if (resultado_lock == -1) {
		throw "Error deslockeando un Pipe. Este es mi fd " + std::to_string(fd);
	}
	return resultado_lock;
}


int Pipe :: getFdLectura () const {
	if ( this->lectura == true )
		return this->descriptores[LECTURA];
	else
		return -1;
}

int Pipe :: getFdEscritura () const {
	if ( this->escritura == true )
		return this->descriptores[ESCRITURA];
	else
		return -1;
}

void Pipe :: cerrar () {
	if ( this->lectura == true ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}

	if ( this->escritura == true ) {
		close ( this->descriptores[1] );
		this->escritura = false;
	}
}
