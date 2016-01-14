/*
 * utils.hpp
 *
 *  Created on: Jan 10, 2016
 *      Author: openwrt
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

namespace ud {

class Utils {
public:
	static void msleep(long ms);
	static void usleep(long ms);
	static void nsleep(long long ms);
};

}



#endif /* UTILS_HPP_ */
