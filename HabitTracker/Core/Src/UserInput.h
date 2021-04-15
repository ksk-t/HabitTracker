/*
 * UserInput.h
 *
 *  Created on: Apr 14, 2021
 *      Author: keisu
 */

#ifndef SRC_USERINPUT_H_
#define SRC_USERINPUT_H_

#include <cstdint>

enum class UserInput_t : uint32_t
{
	Left = 1 << 0,
	Right = 1 << 1,
	Select = 1 << 2
};



#endif /* SRC_USERINPUT_H_ */
