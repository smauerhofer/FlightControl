/*
 * heartbeat.hpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#ifndef HEARTBEAT_HPP_
#define HEARTBEAT_HPP_

#include "thread.hpp"
#include "gpio.hpp"

namespace ud {

class Heartbeat : public Thread {
private:
	GPIO&			io_;
	GPIO::pin_type	pin_;
	int 			on_;
	int 			off_;
	volatile bool	running_;

public:
	Heartbeat(int on_time_ms, int off_time_ms, GPIO::pin_type pin);

	virtual void operator()();
	void stop();
};

}

#endif /* HEARTBEAT_HPP_ */
