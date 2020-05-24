#ifndef SIGABRT_HANDLER_H_
#define SIGABRT_HANDLER_H_

#include <signal.h>
#include <assert.h>
#include <iostream>

#include "EventHandler.h"

class SIGABRT_Handler : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;

	public:

		SIGABRT_Handler () : gracefulQuit(0) {
		}

		~SIGABRT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGABRT );
			std::cout << "Cambio el valor de graceful quit" << endl;
			this->gracefulQuit = 1;
			return 0;
		}

		sig_atomic_t getGracefulQuit () const {
			return this->gracefulQuit;
		}

};

#endif /* SIGINT_HANDLER_H_ */
