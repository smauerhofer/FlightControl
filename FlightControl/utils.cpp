/*
 * utils.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include <time.h>
#include <errno.h>

#include "utils.hpp"

namespace ud {

void Utils::msleep(long ms)
{
	timespec req, rem;
	req.tv_sec = ms / 1000;
	req.tv_nsec = ms % 1000;
	req.tv_nsec *= 1000000;
	while ((nanosleep(&req, &rem) != 0) && (errno == EINTR))
	{
		req = rem;
	}
//	clock_gettime(CLOCK_REALTIME, &req);
//	req.tv_sec += rem.tv_sec;
//	req.tv_nsec += rem.tv_nsec;
//	if (req.tv_nsec >= 1000000000) {
//		++req.tv_sec;
//		req.tv_nsec -= 1000000000;
//	}
//	while ((clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &req, &rem) != 0) && (errno == EINTR)) ;
}

void Utils::usleep(long us)
{
	timespec req, rem;
	req.tv_sec = us / 1000000;
	req.tv_nsec = us % 1000000;
	req.tv_nsec *= 1000;
	while ((nanosleep(&req, &rem) != 0) && (errno == EINTR))
	{
		req = rem;
	}
}

void Utils::nsleep(long long ns)
{
	timespec req, rem;
	req.tv_sec = ns / 1000000000;
	req.tv_nsec = ns % 1000000000;
	while ((nanosleep(&req, &rem) != 0) && (errno == EINTR))
	{
		req = rem;
	}
}

}


