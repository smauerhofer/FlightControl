/*
 * gpio.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "gpio.hpp"

namespace ud {

#define	MEM_BASE	0x18040000
#define	MEM_SIZE	48
#define	MAX_PIN		27

GPIO::GPIO()
: gpio_base_(0)
{
	int mem_id = open("/dev/mem", O_RDWR);
    if (mem_id < 0)
    {
        throw "GPIO::GPIO() open memory device failed";
    }
    gpio_base_ = reinterpret_cast<unsigned long*>(mmap(0, MEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_id, MEM_BASE));
    close(mem_id);
    if (gpio_base_ == MAP_FAILED)
    {
        throw "GPIO::GPIO() memory mapping failed";
   }
}

GPIO::~GPIO()
{
	if (gpio_base_)
	{
		munmap(reinterpret_cast<void*>(MEM_BASE), MEM_SIZE);
		gpio_base_ = 0;
	}
}

GPIO::Direction GPIO::config(pin_type pin)
{
	if (pin > MAX_PIN) {
		throw "GPIO::config() invalid pin";
	}
	register_type old = *(gpio_base_+2);
	register_type mask = 1UL << pin;
	return (old & mask) ? output : input;
}

GPIO::Direction GPIO::config(pin_type pin, Direction dir)
{
	if (pin > MAX_PIN) {
		throw "GPIO::config() invalid pin";
	}
	register_type old = *(gpio_base_+2);
	register_type mask = 1UL << pin;
	if (dir == output)
	{
		*(gpio_base_+2) = old | mask;
	}
	else {
		*(gpio_base_+2) = old & ~mask;
	}
	return (old & mask) ? output : input;
}

GPIO::Value GPIO::read(pin_type pin)
{
	if (pin > MAX_PIN) {
		throw "GPIO::read() invalid pin";
	}
	register_type old = *(gpio_base_+1);
	register_type mask = 1UL << pin;
	return (old & mask) ? high : low;
}

GPIO::Value GPIO::write(pin_type pin, Value val)
{
	if (pin > MAX_PIN) {
		throw "GPIO::write() invalid pin";
	}
	register_type old = *(gpio_base_+1);
	register_type mask = 1UL << pin;
	if (val == high)
	{
		*(gpio_base_+3) = mask;
	}
	else {
		*(gpio_base_+4) = mask;
	}
	return (old & mask) ? high : low;
}

GPIO::Value GPIO::toggle(pin_type pin)
{
	if (pin > MAX_PIN) {
		throw "GPIO::toggle() invalid pin";
	}
	register_type old = *(gpio_base_+1);
	register_type mask = 1UL << pin;
	if (old & mask)
	{
		*(gpio_base_+4) = mask;
		return high;
	}
	*(gpio_base_+3) = mask;
	return low;
}

GPIO& GPIO::instance()
{
	static GPIO* instance = 0;
	if (instance == 0)
	{
		instance = new GPIO();
	}
	return *instance;
}


}

