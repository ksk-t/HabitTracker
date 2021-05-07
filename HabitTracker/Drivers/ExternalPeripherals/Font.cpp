/*
 * Font.cpp
 *
 *  Created on: May 2, 2021
 *      Author: keisu
 */

#include "Font.h"

Character Font::GetChar(const char c)
{
	return m_chars[m_char_map[static_cast<uint8_t>(c)]];
}

constexpr size_t CLOCK_FONT_HEIGHT = 7;

static const uint16_t FONT_CLOCK_DATA_SPACE[CLOCK_FONT_HEIGHT] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
static const uint16_t FONT_CLOCK_DATA_0[CLOCK_FONT_HEIGHT]     = {0xF000,0x9000,0x9000,0x9000,0x9000,0x9000,0xF000};
static const uint16_t FONT_CLOCK_DATA_1[CLOCK_FONT_HEIGHT]     = {0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000};
static const uint16_t FONT_CLOCK_DATA_2[CLOCK_FONT_HEIGHT]     = {0xF000,0x1000,0x1000,0xF000,0x8000,0x8000,0xF000};
static const uint16_t FONT_CLOCK_DATA_3[CLOCK_FONT_HEIGHT]     = {0xF000,0x1000,0x1000,0xF000,0x1000,0x1000,0xF000};
static const uint16_t FONT_CLOCK_DATA_4[CLOCK_FONT_HEIGHT]     = {0x9000,0x9000,0x9000,0xF000,0x1000,0x1000,0x1000};
static const uint16_t FONT_CLOCK_DATA_5[CLOCK_FONT_HEIGHT]     = {0xF000,0x8000,0x8000,0xF000,0x1000,0x1000,0xF000};
static const uint16_t FONT_CLOCK_DATA_6[CLOCK_FONT_HEIGHT]     = {0xF000,0x8000,0x8000,0xF000,0x9000,0x9000,0xF000};
static const uint16_t FONT_CLOCK_DATA_7[CLOCK_FONT_HEIGHT]     = {0xF000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000};
static const uint16_t FONT_CLOCK_DATA_8[CLOCK_FONT_HEIGHT]     = {0xF000,0x9000,0x9000,0xF000,0x9000,0x9000,0xF000};
static const uint16_t FONT_CLOCK_DATA_9[CLOCK_FONT_HEIGHT]     = {0xF000,0x9000,0x9000,0xF000,0x1000,0x1000,0x1000};
static const uint16_t FONT_CLOCK_DATA_COLON[CLOCK_FONT_HEIGHT] = {0x0000,0x0000,0x8000,0x0000,0x8000,0x0000,0x0000};
static const uint16_t FONT_CLOCK_DATA_A[CLOCK_FONT_HEIGHT]     = {0xF000,0x9000,0x9000,0xF000,0x9000,0x9000,0x9000};
static const uint16_t FONT_CLOCK_DATA_P[CLOCK_FONT_HEIGHT]     = {0xF000,0x9000,0x9000,0xF000,0x8000,0x8000,0x8000};
static const uint16_t FONT_CLOCK_DATA_M[CLOCK_FONT_HEIGHT]     = {0x8800,0xD800,0xA800,0x8800,0x8800,0x8800,0x8800};

static const Character FONT_CLOCK_SPACE{FONT_CLOCK_DATA_SPACE, 1};
static const Character FONT_CLOCK_0{FONT_CLOCK_DATA_0, 4};
static const Character FONT_CLOCK_1{FONT_CLOCK_DATA_1, 4};
static const Character FONT_CLOCK_2{FONT_CLOCK_DATA_2, 4};
static const Character FONT_CLOCK_3{FONT_CLOCK_DATA_3, 4};
static const Character FONT_CLOCK_4{FONT_CLOCK_DATA_4, 4};
static const Character FONT_CLOCK_5{FONT_CLOCK_DATA_5, 4};
static const Character FONT_CLOCK_6{FONT_CLOCK_DATA_6, 4};
static const Character FONT_CLOCK_7{FONT_CLOCK_DATA_7, 4};
static const Character FONT_CLOCK_8{FONT_CLOCK_DATA_8, 4};
static const Character FONT_CLOCK_9{FONT_CLOCK_DATA_9, 4};
static const Character FONT_CLOCK_COLON{FONT_CLOCK_DATA_COLON, 1};
static const Character FONT_CLOCK_A{FONT_CLOCK_DATA_A, 4};
static const Character FONT_CLOCK_P{FONT_CLOCK_DATA_P, 4};
static const Character FONT_CLOCK_M{FONT_CLOCK_DATA_M, 5};

static const Character char_list[] = {
		FONT_CLOCK_0,
		FONT_CLOCK_1,
		FONT_CLOCK_2,
		FONT_CLOCK_3,
		FONT_CLOCK_4,
		FONT_CLOCK_5,
		FONT_CLOCK_6,
		FONT_CLOCK_7,
		FONT_CLOCK_8,
		FONT_CLOCK_9,
		FONT_CLOCK_COLON,
		FONT_CLOCK_A,
		FONT_CLOCK_P,
		FONT_CLOCK_SPACE,
		FONT_CLOCK_M
};
static const uint8_t char_map[256] =
{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 0,
		0, 0, 0, 0, 0, 11, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 14, 0, 0,
		12, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0
}; // Index = ascii value, value at index = index of ascii character in m_chars

Font ClockFont{char_list, CLOCK_FONT_HEIGHT, char_map};
