/*
 * Color.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

struct Color_t
{
	Color_t (uint8_t r_val = 0, uint8_t g_val = 0, uint8_t b_val = 0) :
		R(r_val),
		G(g_val),
		B(b_val) {}

	uint8_t R{0};
	uint8_t G{0};
	uint8_t B{0};

	bool operator==(const Color_t &c)
		{
			return (R == c.R) && (G == c.G) && (B == c.B);
		}
};

struct BasicColors
{
	static const Color_t Black;
	static const Color_t White;
};

#endif /* COLOR_H_ */
