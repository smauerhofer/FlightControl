/*
 * gpio.hpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

namespace ud {

class GPIO {
private:
	typedef unsigned long register_type;
	volatile register_type* gpio_base_;

	GPIO();
	~GPIO();

public:
	static GPIO& instance();

	enum Direction {
		input,
		output
	};

	enum Value {
		low,
		high
	};

	typedef unsigned int pin_type;

	// read direction
	Direction config(pin_type pin);

		// set new direction and return old one
	Direction config(pin_type pin, Direction dir);

	Value read(pin_type pin);

		// set new state and return old state
	Value write(pin_type pin, Value);

	// invert pin state and return old state
	Value toggle(pin_type pin);

};

}

#endif /* GPIO_HPP_ */
