/*
 * StringUtilities.h
 *
 *  Created on: May 19, 2021
 *      Author: keisu
 */

#ifndef SRC_STRINGUTILITIES_H_
#define SRC_STRINGUTILITIES_H_

#include <stdint.h>
#include <stddef.h>

class StringUtilities
{
public:
	static uint32_t SplitToUint(uint8_t* buffer, size_t buffer_size, const char delimiter, uint32_t* output_buffer, size_t output_buffer_size);
private:
	static bool IsNumeric(uint8_t* buffer, size_t buffer_size);
};

#endif /* SRC_STRINGUTILITIES_H_ */
