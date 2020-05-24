#ifndef SIGABRT_HANDLER_H_
#define SIGABRT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class SIGABRT_Handler : public EventHandler {

	private:
		sig_atomic_t readingForbidden;

	public:

		SIGABRT_Handler () : readingForbidden(0) {
		}

		~SIGABRT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGABRT );
			this->readingForbidden = 1;
			return 0;
		}

		sig_atomic_t getReadingForbidden () const {
			return this->readingForbidden;
		}

};

#endif /* SIGINT_HANDLER_H_ */
