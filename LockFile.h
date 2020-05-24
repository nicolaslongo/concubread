#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/file.h>

const char* const READ_MODE = "r";
const char* const WRITE_MODE = "w";

class LockFile {

private:
	struct flock fl;
	int fd;
	std::string nombre;

protected:

public:
	FILE* file;
	LockFile ( const std::string nombre, const char* mode );
	~LockFile();

	int tomarLockEscritura();
	int tomarLockLectura();
	int liberarLock ();
	ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
	ssize_t leer ( void* buffer,const ssize_t buffsize );

};

#endif /* LOCKFILE_H_ */
