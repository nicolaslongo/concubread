#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"

#include <iostream>

class FifoLectura : public Fifo {

	private:
		struct flock fl;

	public:
		FifoLectura(const std::string nombre);
		~FifoLectura();

		void abrir();
		ssize_t leer(void* buffer,const ssize_t buffsize) const;
};

#endif /* FIFOLECTURA_H_ */
