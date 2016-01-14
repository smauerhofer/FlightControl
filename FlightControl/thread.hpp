/*
 * thread.hpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include <pthread.h>

#ifndef THREAD_HPP_
#define THREAD_HPP_

namespace ud {

class Thread {
private:
	pthread_t		handle_;
	volatile bool	running_;

	static void* run_thread(void*);

public:
	Thread();
	virtual ~Thread();

	virtual void start();

	virtual void operator()()=0;
};


}



#endif /* THREAD_HPP_ */
