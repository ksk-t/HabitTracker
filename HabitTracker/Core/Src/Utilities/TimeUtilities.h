/*
 * TimeUtilities.h
 *
 *  Created on: Apr 7, 2021
 *      Author: keisu
 */

#ifndef SRC_TIMEUTILITIES_H_
#define SRC_TIMEUTILITIES_H_

#include <cstdint>

class TimeUtilities
{
public:
	static bool HasElapsed(uint32_t interval, uint32_t start, uint32_t end);
};


#endif /* SRC_TIMEUTILITIES_H_ */
