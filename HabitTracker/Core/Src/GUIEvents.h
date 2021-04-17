/*
 * UserInput.h
 *
 *  Created on: Apr 14, 2021
 *      Author: keisu
 */

#ifndef SRC_GUIEVENTS_H_
#define SRC_GUIEVENTS_H_

#include <cstdint>

enum class GUIEvents_t : uint32_t
{
	EncoderLeft = 1 << 0,
	EncoderRight = 1 << 1,
	ButtonSelect = 1 << 2,
	ResetHabits = 1 << 3
};



#endif /* SRC_GUIEVENTS_H_ */
