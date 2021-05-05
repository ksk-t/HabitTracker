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


