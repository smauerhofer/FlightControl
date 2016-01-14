/*
 * heartbeat.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include "heartbeat.hpp"
#include "utils.hpp"

namespace ud {

Heartbeat::Heartbeat(int on_time_ms, int off_time_ms, GPIO::pin_type pin)
: io_(GPIO::instance())
, pin_(pin)
, on_(on_time_ms)
, off_(off_time_ms)
, running_(false)
{
}

void Heartbeat::operator()()
{
	running_ = true;
	while (running_)
	{
		// LED on
		io_.write(pin_, GPIO::low);
		Utils::msleep(on_);
		// LED off
		io_.write(pin_, GPIO::high);
		Utils::msleep(off_);
	}
}

void Heartbeat::stop()
{
	running_ = false;
}

}

