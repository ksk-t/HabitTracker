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

