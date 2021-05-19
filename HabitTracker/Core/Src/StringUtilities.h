/*
 * StringUtilities.h
 *
 *  Created on: May 19, 2021
 *      Author: keisu
 */

#ifndef SRC_STRINGUTILITIES_H_
#define SRC_STRINGUTILITIES_H_

#include <string>

class StringUtilities
{
public:
	static uint32_t SplitToUint(std::string str,  const char delimiter, uint32_t* output_buffer, size_t buffer_size);
private:
	static bool IsNumeric(std::string str);
};

#endif /* SRC_STRINGUTILITIES_H_ */
