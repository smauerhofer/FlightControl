/*
 * spi.hpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#ifndef SPI_HPP_
#define SPI_HPP_

namespace ud {

class SPI {
private:
	int		handle_;

public:
	SPI(const char* dev);
	~SPI();

	int transfer(int size, void* in, const void* out);

};


}

#endif /* SPI_HPP_ */
