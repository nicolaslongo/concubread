#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>


class LockFile {

private:
	struct flock fl;
	int fd;
	std::string nombre;

protected:

public:
	LockFile ( const std::string nombre );
	~LockFile();

	int tomarLock();
	int liberarLock ();
	ssize_t escribir ( const char* buffer,const ssize_t buffsize ) const;
	ssize_t leer ( void* buffer,const ssize_t buffsize );

};

#endif /* LOCKFILE_H_ */
