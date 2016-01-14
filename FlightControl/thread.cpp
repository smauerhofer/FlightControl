/*
 * thread.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include "thread.hpp"
#include <iostream>

namespace ud {

void* Thread::run_thread(void* par)
{
	Thread* thr = reinterpret_cast<Thread*>(par);
	try
	{
		(*thr)();
	}
	catch (const char* txt)
	{
		std::cerr << "Thread ERROR " << txt << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown Thread ERROR " << std::endl;
	}
	thr->running_ = false;
	return 0;
}

Thread::Thread()
: handle_(0)
, running_(false)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
	if (!running_)
	{
		running_ = true;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int err = pthread_create(&handle_, &attr, &run_thread, this);
		pthread_attr_destroy(&attr);
		if (err) {
			throw "Thread::start failed";
		}
	}
}


}



