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

extern Font ClockFont;

#endif /* EXTERNALPERIPHERALS_FONT_H_ */
