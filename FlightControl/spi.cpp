/*
 * spi.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>

#include "spi.hpp"


namespace ud {

SPI::SPI(const char* dev)
: handle_(0)
{
	int h = open(dev, O_RDWR);
	if (h < 0)
	{
		throw "SPI::SPI() open failed";
	}
	handle_ = h;
}

SPI::~SPI()
{
	if (handle_) {
		close(handle_);
	}
}

int SPI::transfer(int size, void* in, const void* out)
{
    struct spi_ioc_transfer xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.tx_buf = (unsigned long)out;
    xfer.rx_buf = (unsigned long)in;
    xfer.len = size;
    return ioctl(handle_, SPI_IOC_MESSAGE(1), &xfer);
}


}


