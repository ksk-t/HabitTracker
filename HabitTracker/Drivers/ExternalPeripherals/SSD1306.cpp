/*
 * SSD1306.cpp
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

/*
 * SSD1306.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: keisu

 * Data Frame (aka. _buffer array) pixel layout
 *
 *   <------ 128 Pixel Wide ------->
 *    First 128 Bytes = first 8 rows
 *                           Each Byte is one pixel wide
 *   -------------------------------  ^
 *   B                           B|B  |
 *   Y                           Y|Y  |  8 Pixels high per byte
 *   T                           Y|T  |
 *   E                           E|E  |
 *   1         <...              1|0  |
 *   2                           #|#  |
 *   7                           #|#  |
 *   #                           #|#  |
 *   -------------------------------  V
 *                                 B
 *                                 Y
 *                                 T
 *                                 E
 *              <...               1
 *                                 2
 *                                 8
 *                                 #
 * ---------------------------------
 */


//
#include "SSD1306.h"

//SSD1306::SSD1306(I2C_HandleTypeDef i2c_handler) :
//	_is_enabled(false),
//	_i2c_handler(NULL)
//{
//	_draw_string_setting.SetFont(&Font_7x10);
//	_draw_string_setting.SetColor(Color::GetColor(BasicColor::White));
//}

void SSD1306::Initialize()
{
	this->WriteCommand(CMD::SET_MEM_ADDR_MODE);
	this->WriteCommand(CMD::PAGE_START_ADDR);
	this->WriteCommand(CMD::COM_SCAN_DIR_63_TO_0);
	this->WriteCommand(CMD::LOW_COLUMN_ADDR_0);
	this->WriteCommand(CMD::HIGH_COLUMN_ADDR_0);
	this->WriteCommand(CMD::START_LINE_ADDR_0);
	this->SetContrast(0xFF);
	this->WriteCommand(CMD::INVERSE_OFF);
	this->WriteCommand(CMD::MULTIPLEX_RATIO_1_64);
	this->WriteCommand(CMD::UNKNOWN);
	this->WriteCommand(CMD::OUTPUT_FOLLOWS_RAM);
	this->WriteCommand(CMD::SET_DISPLAY_OFFSET);
	this->WriteCommandByte(0x00);
	this->WriteCommand(CMD::SET_DISPLAY_CLOCK_RATIO);
	this->WriteCommandByte(0xF0);
	this->WriteCommand(CMD::SET_PRECHARGE_PERIOD);
	this->WriteCommandByte(0x22);
	this->WriteCommand(CMD::SET_COM_PIN_HW_CONFIG);
	this->WriteCommandByte(0x12);
	this->WriteCommand(CMD::SET_VCOMH);
	this->WriteCommandByte(0x20);
	this->WriteCommand(CMD::SET_DCDC_ENABLE);
	this->WriteCommandByte(0x14);
	this->SetDisplayEnable(true);
}

void SSD1306::WriteCommandByte(uint8_t byte)
{
	HAL_I2C_Mem_Write(m_i2c_handler, I2C_ADDR, 0x00, 1, &byte, 1, HAL_MAX_DELAY);
}

void SSD1306::WriteCommandBytes(uint8_t* buffer, size_t buffer_size)
{
	HAL_I2C_Mem_Write(m_i2c_handler, I2C_ADDR, 0x40, 1, buffer, buffer_size, HAL_MAX_DELAY);
}

void SSD1306::WriteCommand(CMD cmd)
{
	this->WriteCommandByte((uint8_t)cmd);
}

void SSD1306::SetDisplayEnable(bool enable)
{
	CMD value;

    if (enable)
    {
        value = CMD::DISPLAY_ON;
	} else
	{
		value = CMD::DISPLAY_OFF;

	}

    this->WriteCommand(value);
    m_is_enabled = enable;
}

void  SSD1306::SetContrast(const uint8_t value)
{
	this->WriteCommand(CMD::SET_CONTRAST);
	this->WriteCommandByte(value);
}

void SSD1306::Update()
{
    for(uint8_t i = 0; i < HEIGHT/8; i++) {
        this->WriteCommandByte(0xB0 + i); // Set the current RAM page address.
        this->WriteCommandByte(0x00);
        this->WriteCommandByte(0x10);
        this->WriteCommandBytes(&m_buffer[WIDTH*i], WIDTH);
    }

}

void SSD1306::DrawPixel(Point_t point, Color_t color)
{
    if(point.X >= WIDTH || point.Y >= HEIGHT)
    {
        // Don't write outside the buffer
        return;
    }

    if(color == BasicColors::Black())
    {
    	m_buffer[point.X + (point.Y / 8) * WIDTH] &= ~(1 << (point.Y % 8));
    } else
    {
    	m_buffer[point.X + (point.Y / 8) * WIDTH] |= 1 << (point.Y % 8);
    }
}
//
//status_t SSD1306::InvertPixel(uint32_t x, uint32_t y)
//{
//	if (x >= WIDTH || y >= HEIGHT)
//	{
//		return STATUS_ERROR;
//	}
//
//	_buffer[x + (y / 8) * WIDTH] ^= 1 << (y % 8);
//
//	return STATUS_OK;
//}
//
//status_t SSD1306::InvertRegion(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
//{
//	if (x1 >= WIDTH || x2 >= WIDTH || y1 >= HEIGHT || y2 >= HEIGHT)
//	{
//		return STATUS_ERROR;
//	}
//
//	uint32_t x_pos = (x1 < x2) ? x1 : x2;
//	uint32_t x_end = (x1 < x2) ? x2 : x2;
//	uint32_t y_start = (y1 < y2) ? y1 : y2;
//	uint32_t y_pos;
//	uint32_t y_end = (y1 < y2) ? y2 : y1;
//
//	for (;x_pos <= x_end;x_pos++)
//	{
//		for (y_pos = y_start; y_pos <= y_end; y_pos++)
//		{
//			this->InvertPixel(x_pos, y_pos);
//		}
//
//	}
//
//	return STATUS_OK;
//}

//status_t SSD1306::DrawStringWrap(const std::string str)
//{
//	if (str.length() == 0)
//	{
//		return STATUS_OK;
//	}
//
//	uint32_t y = HEIGHT - 1 - _draw_string_setting.GetFont()->FontHeight; // - 1 since HEIGHT is 64 but the max height value is 63
//	const size_t max_lines = 10;
//	std::string lines[max_lines];
//	size_t num_lines = this->WrapText(str, lines, max_lines);
//	if (num_lines == 0)
//	{
//		return STATUS_ERROR;
//	}
//
//	for (size_t i = 0; i < num_lines; i++)
//	{
//		this->DrawString(0, y, lines[i]);
//		y -= _draw_string_setting.GetFont()->FontHeight;
//	}
//
//	return STATUS_OK;
//}
//
//status_t SSD1306::Clear()
//{
//	return this->Fill(_default_fill);
//}
//
//bool SSD1306::RefreshRequired()
//{
//	if (refresh_interval == 0)
//	{
//		return false;
//	}
//
//	uint32_t now = HAL_GetTick();
//	if (now >= _last_update)
//	{
//		return (now - _last_update) >= refresh_interval;
//	} else
//	{
//		// Rollover has occured
//		return (now + (UINT32_MAX - _last_update)) >= refresh_interval;
//	}
//
//}
//
//size_t SSD1306::WrapText(std::string input, std::string output[], size_t max_num_lines)
//{
//	const size_t max_words = 100;
//	std::string words[max_words];
//	size_t current_line_index = 0;
//	std::string current_line = "";
//	uint32_t font_width = _draw_string_setting.GetFont()->FontWidth;
//	uint32_t max_characters_per_line = WIDTH / font_width;
//
//	size_t num_words = SplitString(input, words, max_words);
//	if ( num_words > max_words)
//	{
//		return 0;
//	}
//
//	for (size_t i = 0; i < num_words; i++)
//	{
//		size_t line_length = current_line.length() + words[i].length()	;
//		if (words[i] == "\n")
//		{// New line
//			if (current_line.length() > 0)
//			{// End current line as it is and move on to next line
//				output[current_line_index++] = current_line;
//				current_line = "";
//			}else
//			{// Create empty line
//				output[current_line_index++] = "";
//			}
//		}
//		else if (line_length == max_characters_per_line && current_line.length() == 0)
//		{// Current line is empty and next word is equal to the maximum number of characters per line
//			output[current_line_index++] = words[i];
//		}
//		else if ((1 + line_length) > max_characters_per_line) // the + 1 is for the space
//		{// space + next word is too long
//			output[current_line_index++] = current_line;
//			current_line = "";
//
//			// Kind of a hack but decrement i so that the word that would have
//			// went out of bounds can be drawn in the next line
//			i--;
//		}else
//		{// Enough room is available for a space + the next word
//			if (current_line.length() > 0) // do not add a space if first word in line
//			{
//				current_line += " ";
//			}
//			current_line += words[i];
//		}
//	}
//
//	if (current_line.length() > 0)
//	{
//		output[current_line_index++] = current_line;
//		current_line = "";
//	}
//
//	return current_line_index;
//}
//
//size_t SSD1306::SplitString(std::string input, std::string output[], size_t max_num_words)
//{
//	std::string current_word = "";
//	size_t current_word_index = 0;
//
//	for (std::string::const_iterator iter = input.begin(); iter != input.end(); iter++)
//	{
//		if (*iter == '\n')
//		{
//			// Add current string of characters as a word
//			if (current_word.length() > 0)
//			{
//				if (current_word_index < max_num_words)
//				{
//					output[current_word_index] = current_word;
//					current_word = "";
//				}
//				current_word_index++;
//
//			}
//
//			// Add the newline as its own "word"
//			if (current_word_index < max_num_words)
//			{
//				output[current_word_index] = "\n";
//			}
//
//			current_word_index++;
//
//		}else if (*iter == ' ')
//		{
//			// Add current string of characters as a word
//			if (current_word.length() > 0)
//			{
//				if (current_word_index < max_num_words)
//				{
//					output[current_word_index] = current_word;
//					current_word = "";
//				}
//				current_word_index++;
//
//			}else
//			{
//				// Throw away space character if current word length is empty;
//			}
//
//		}else
//		{
//			// Check if adding character will make word longer than width of screen
//			if ((current_word.length() + 1) * _draw_string_setting.GetFont()->FontWidth < WIDTH)
//			{// If not add character
//				current_word += *iter;
//			}else
//			{// If yes, cut off word and continue the word onto the next string
//				if (current_word_index < max_num_words)
//				{
//					output[current_word_index] = current_word;
//					current_word = *iter;
//				}
//				current_word_index++;
//
//			}
//		}
//	}
//
//	// Add any remaining characters as a word
//	if (current_word.length() > 0)
//	{
//		if (current_word_index < max_num_words)
//		{
//			output[current_word_index] = current_word;
//			current_word = "";
//		}
//		current_word_index++;
//
//	}
//	return current_word_index;
//}


