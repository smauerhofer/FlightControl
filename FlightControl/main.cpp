/*
 * main.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include <iostream>

#include "heartbeat.hpp"
#include "utils.hpp"


int main(int argc, char* argv[])
{
	try {
		std::cout << "Flight Computer 1.0" << std::endl;

		ud::Heartbeat* heartbeat = new ud::Heartbeat(100, 1400, 27);
		heartbeat->start();
		for (;;) {
			ud::Utils::usleep(10000000);
		}
	}
	catch (const char* txt)
	{
		std::cerr << "ERROR " << txt << std::endl;
		return 2;
	}
	catch (...)
	{
		return 1;
	}
	return 0;
}


