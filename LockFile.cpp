#include "LockFile.h"

LockFile :: LockFile ( const std::string nombre, const char* mode ) {

	this->nombre = nombre;
	// if (mode == READ_MODE) {
	// 	this->fl.l_type = F_RDLCK;
	// }
	// else if (mode == WRITE_MODE) {
	// 	this->fl.l_type = F_WRLCK;
	// }
	// this->fl.l_whence = SEEK_SET;
	// this->fl.l_start = 0;
	// this->fl.l_len = 0;
	this->file = fopen ( this->nombre.c_str(), mode );
	this->fd = fileno(this->file);
}

int LockFile::tomarLockEscritura() {
	// this->fl.l_type = F_WRLCK;
	// return fcntl ( this->fd,F_SETLKW,&(this->fl) );
	return flock(this->fd, LOCK_EX);
}

int LockFile::tomarLockLectura() {
	// this->fl.l_type = F_RDLCK;
	// return fcntl (this->fd, F_SETLKW, &(this->fl));
	return flock(this->fd, LOCK_SH);
}

int LockFile :: liberarLock () {
	// this->fl.l_type = F_UNLCK;
	// return fcntl ( this->fd,F_SETLK,&(this->fl) );
	return flock(this->fd, LOCK_UN);

}

ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
	lseek ( this->fd,0,SEEK_END );
	return write ( this->fd,buffer,buffsize );
}

ssize_t LockFile :: leer ( void* buffer, const ssize_t buffsize ) {
	lseek ( this->fd,0,SEEK_END );
	return read ( this->fd,buffer,buffsize );
}

LockFile :: ~LockFile () {
	close ( this->fd );
}
