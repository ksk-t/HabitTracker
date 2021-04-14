/*
 * RotaryEncoder.cpp
 *
 *  Created on: Apr 12, 2021
 *      Author: keisu
 */

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint16_t init_pos) : m_prev_pos(init_pos)
{
}

bool RotaryEncoder::HasMoved(uint16_t current_pos)
{
	uint16_t encoder_diff = current_pos - m_prev_pos;
	if (encoder_diff <= 65534 && encoder_diff >= 2) // This ensures that there is at least a difference of 2 in the count value. 1 notch on the encoder = 2 counter values
	{
		m_prev_pos = current_pos;
		return true;
	}

	return false;
}
