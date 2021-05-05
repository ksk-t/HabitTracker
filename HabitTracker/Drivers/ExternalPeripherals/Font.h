/*
 * Font.h
 *
 *  Created on: May 2, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_FONT_H_
#define EXTERNALPERIPHERALS_FONT_H_

#include <cstdint>
#include <cstddef>

struct Character
{
	Character(const uint16_t* data, size_t width) : Data(data), Width(width) {};

	const uint16_t* Data;
	const size_t Width;
};

class Font
{
public:
	Font(const Character* chars, size_t height, const uint8_t* char_map) : Height(height), m_chars(chars), m_char_map(char_map) {};
	Character GetChar(const char c);
	const size_t Height;
private:
	const Character* m_chars;
	const uint8_t* m_char_map;
};

constexpr size_t CLOCK_FONT_HEIGHT = 7;

const uint16_t FONT_CLOCK_DATA_SPACE[CLOCK_FONT_HEIGHT] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
const uint16_t FONT_CLOCK_DATA_0[CLOCK_FONT_HEIGHT] = {0xF000,0x9000,0x9000,0x9000,0x9000,0x9000,0xF000};
const uint16_t FONT_CLOCK_DATA_1[CLOCK_FONT_HEIGHT] = {0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000};
const uint16_t FONT_CLOCK_DATA_2[CLOCK_FONT_HEIGHT] = {0xF000,0x1000,0x1000,0xF000,0x8000,0x8000,0xF000};
const uint16_t FONT_CLOCK_DATA_3[CLOCK_FONT_HEIGHT] = {0xF000,0x1000,0x1000,0xF000,0x1000,0x1000,0xF000};
const uint16_t FONT_CLOCK_DATA_4[CLOCK_FONT_HEIGHT] = {0x9000,0x9000,0x9000,0xF000,0x1000,0x1000,0x1000};
const uint16_t FONT_CLOCK_DATA_5[CLOCK_FONT_HEIGHT] = {0xF000,0x8000,0x8000,0xF000,0x1000,0x1000,0xF000};
const uint16_t FONT_CLOCK_DATA_6[CLOCK_FONT_HEIGHT] = {0xF000,0x8000,0x8000,0xF000,0x9000,0x9000,0xF000};
const uint16_t FONT_CLOCK_DATA_7[CLOCK_FONT_HEIGHT] = {0xF000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000};
const uint16_t FONT_CLOCK_DATA_8[CLOCK_FONT_HEIGHT] = {0xF000,0x9000,0x9000,0xF000,0x9000,0x9000,0xF000};
const uint16_t FONT_CLOCK_DATA_9[CLOCK_FONT_HEIGHT] = {0xF000,0x9000,0x9000,0xF000,0x1000,0x1000,0x1000};
const uint16_t FONT_CLOCK_DATA_COLON[CLOCK_FONT_HEIGHT] = {0x0000,0x0000,0x8000,0x0000,0x8000,0x0000,0x0000};
const uint16_t FONT_CLOCK_DATA_A[CLOCK_FONT_HEIGHT] = {0xF000,0x9000,0x9000,0xF000,0x9000,0x9000,0x9000};
const uint16_t FONT_CLOCK_DATA_P[CLOCK_FONT_HEIGHT] = {0xF000,0x9000,0x9000,0xF000,0x8000,0x8000,0x8000};

const Character FONT_CLOCK_SPACE{FONT_CLOCK_DATA_SPACE, 1};
const Character FONT_CLOCK_0{FONT_CLOCK_DATA_0, 4};
const Character FONT_CLOCK_1{FONT_CLOCK_DATA_1, 1};
const Character FONT_CLOCK_2{FONT_CLOCK_DATA_2, 4};
const Character FONT_CLOCK_3{FONT_CLOCK_DATA_3, 4};
const Character FONT_CLOCK_4{FONT_CLOCK_DATA_4, 4};
const Character FONT_CLOCK_5{FONT_CLOCK_DATA_5, 4};
const Character FONT_CLOCK_6{FONT_CLOCK_DATA_6, 4};
const Character FONT_CLOCK_7{FONT_CLOCK_DATA_7, 4};
const Character FONT_CLOCK_8{FONT_CLOCK_DATA_8, 4};
const Character FONT_CLOCK_9{FONT_CLOCK_DATA_9, 4};
const Character FONT_CLOCK_COLON{FONT_CLOCK_DATA_COLON, 1};
const Character FONT_CLOCK_A{FONT_CLOCK_DATA_A, 4};
const Character FONT_CLOCK_P{FONT_CLOCK_DATA_P, 4};

const Character char_list[] = {FONT_CLOCK_0, FONT_CLOCK_1, FONT_CLOCK_2, FONT_CLOCK_3, FONT_CLOCK_4, FONT_CLOCK_5, FONT_CLOCK_6, FONT_CLOCK_7, FONT_CLOCK_8, FONT_CLOCK_9, FONT_CLOCK_COLON, FONT_CLOCK_A, FONT_CLOCK_P, FONT_CLOCK_SPACE};
const uint8_t char_map[256] =
{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 0,
		0, 0, 0, 0, 0, 11, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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

const Font ClockFont{char_list, CLOCK_FONT_HEIGHT, char_map};

#endif /* EXTERNALPERIPHERALS_FONT_H_ */
