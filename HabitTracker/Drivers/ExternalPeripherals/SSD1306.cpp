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
#include <string>

// Module name used for logging
static const std::string MODULE_NAME = "SSD1306: ";

#define CHECK_HAL_STATUS(status_to_check)({ if (status_to_check != HAL_OK) return Status_t::ERROR; else return Status_t::OK; })

Status_t SSD1306::Initialize()
{
	Status_t status = Status_t::OK;
	status |= this->WriteCommand(CMD::SET_MEM_ADDR_MODE);
	status |= this->WriteCommand(CMD::PAGE_START_ADDR);
	status |= this->WriteCommand(CMD::COM_SCAN_DIR_63_TO_0);
	status |= this->WriteCommand(CMD::LOW_COLUMN_ADDR_0);
	status |= this->WriteCommand(CMD::HIGH_COLUMN_ADDR_0);
	status |= this->WriteCommand(CMD::START_LINE_ADDR_0);
	status |= this->SetContrast(0xFF);
	status |= this->WriteCommand(CMD::INVERSE_OFF);
	status |= this->WriteCommand(CMD::MULTIPLEX_RATIO_1_64);
	status |= this->WriteCommand(CMD::UNKNOWN);
	status |= this->WriteCommand(CMD::OUTPUT_FOLLOWS_RAM);
	status |= this->WriteCommand(CMD::SET_DISPLAY_OFFSET);
	status |= this->WriteCommandByte(0x00);
	status |= this->WriteCommand(CMD::SET_DISPLAY_CLOCK_RATIO);
	status |= this->WriteCommandByte(0xF0);
	status |= this->WriteCommand(CMD::SET_PRECHARGE_PERIOD);
	status |= this->WriteCommandByte(0x22);
	status |= this->WriteCommand(CMD::SET_COM_PIN_HW_CONFIG);
	status |= this->WriteCommandByte(0x12);
	status |= this->WriteCommand(CMD::SET_VCOMH);
	status |= this->WriteCommandByte(0x20);
	status |= this->WriteCommand(CMD::SET_DCDC_ENABLE);
	status |= this->WriteCommandByte(0x14);
	status |= this->SetDisplayEnable(true);

	return status;
}

Status_t SSD1306::WriteCommandByte(uint8_t byte)
{
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(m_i2c_handler, I2C_ADDR, 0x00, 1, &byte, 1, HAL_MAX_DELAY);
	CHECK_HAL_STATUS(status);
}

Status_t SSD1306::WriteCommandBytes(uint8_t* buffer, size_t buffer_size)
{
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(m_i2c_handler, I2C_ADDR, 0x40, 1, buffer, buffer_size, HAL_MAX_DELAY);
	CHECK_HAL_STATUS(status);
}

Status_t SSD1306::WriteCommand(CMD cmd)
{
	return WriteCommandByte((uint8_t)cmd);
}

Status_t SSD1306::SetDisplayEnable(bool enable)
{
	CMD value;
	Status_t status = Status_t::OK;

    if (enable)
    {
        value = CMD::DISPLAY_ON;
	} else
	{
		value = CMD::DISPLAY_OFF;

	}

    status = this->WriteCommand(value);
    m_is_enabled = enable;

    return status;
}

Status_t  SSD1306::SetContrast(const uint8_t value)
{
	Status_t status = Status_t::OK;
	status |= WriteCommand(CMD::SET_CONTRAST);
	status |= WriteCommandByte(value);
	return status;
}

Status_t SSD1306::Update()
{
	Status_t status = Status_t::OK;
    for(uint8_t i = 0; i < HEIGHT/8; i++) {
    	status |= this->WriteCommandByte(0xB0 + i); // Set the current RAM page address.
    	status |= this->WriteCommandByte(0x00);
    	status |= this->WriteCommandByte(0x10);
    	status |= this->WriteCommandBytes(&m_buffer[WIDTH*i], WIDTH);
    }

    return status;
}

Status_t SSD1306::DrawPixel(Point_t point, Color_t color)
{
    if(point.X >= WIDTH || point.Y >= HEIGHT)
    {
        // Don't write outside the buffer
        return Status_t::OK;
    }

    if(color == BasicColors::Black)
    {
    	m_buffer[point.X + (point.Y / 8) * WIDTH] &= ~(1 << (point.Y % 8));
    } else
    {
    	m_buffer[point.X + (point.Y / 8) * WIDTH] |= 1 << (point.Y % 8);
    }

    return Status_t::OK;
}

