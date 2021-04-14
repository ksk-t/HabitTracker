/*
 * RotaryEncoder.h
 *
 *  Created on: Apr 12, 2021
 *      Author: keisu
 *
 * NOTE: This only works for a 16 bit encoder
 *
 */

#ifndef EXTERNALPERIPHERALS_ROTARYENCODER_H_
#define EXTERNALPERIPHERALS_ROTARYENCODER_H_

#include <cstdint>

class RotaryEncoder
{
public:
	RotaryEncoder(uint16_t init_pos);
	bool HasMoved(uint16_t current_pos);
private:
	uint16_t m_prev_pos;

};

#endif /* EXTERNALPERIPHERALS_ROTARYENCODER_H_ */
