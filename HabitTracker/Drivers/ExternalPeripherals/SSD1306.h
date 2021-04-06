/*
 * SSD1306.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */


/*
 * SSD1306.h
 *
 *  Created on: Aug 29, 2020
 *      Author: keisu
 */

#ifndef DISPLAY_SSD1306_SSD1306_H_
#define DISPLAY_SSD1306_SSD1306_H_

#include "Display.h"
#include "stm32f2xx_hal.h"

class SSD1306 : public Display
{
public:
	SSD1306(I2C_HandleTypeDef* i2c_handler) :
		m_i2c_handler(i2c_handler){};

	Status_t Initialize() override;
	Status_t Update() override;
	Status_t DrawPixel(Point_t point, Color_t color) override;
	Status_t SetContrast(const uint8_t contrast);

	uint32_t GetHeight() { return HEIGHT; };
	uint32_t GetWidth()  { return WIDTH;  };
private:
	static const uint32_t HEIGHT = 64;
	static const uint32_t WIDTH = 128;
	static const uint16_t I2C_ADDR = (0x3C << 1);
	static const uint32_t BUFFER_SIZE = WIDTH * HEIGHT / 8;

	// Command List
	enum class CMD : uint8_t
	{
		// Memory addressing modes
		HOR_ADDR_MODE           = 0x00,

		SET_MEM_ADDR_MODE       = 0x20,
		DISPLAY_ON              = 0xAF,
		DISPLAY_OFF             = 0xAE,
		PAGE_START_ADDR         = 0xB0,
		COM_SCAN_DIR_63_TO_0    = 0xC8,
	    LOW_COLUMN_ADDR_0       = 0x00,
		HIGH_COLUMN_ADDR_0      = 0x10,
		START_LINE_ADDR_0       = 0x40,
		SET_CONTRAST            = 0x81,
		SEG_REMAP_0_127         = 0xA1,
		INVERSE_OFF             = 0xA6,
		MULTIPLEX_RATIO_1_64    = 0xA8,
		UNKNOWN                 = 0x3F, // From reference project, not sure what this does exactly
		OUTPUT_FOLLOWS_RAM      = 0xA4,
		SET_DISPLAY_OFFSET      = 0xD3,
		SET_DISPLAY_CLOCK_RATIO = 0xD5,
		SET_PRECHARGE_PERIOD    = 0xD9,
		SET_COM_PIN_HW_CONFIG   = 0xDA,
		SET_VCOMH               = 0xDB,
		SET_DCDC_ENABLE         = 0x8D,

	};

	uint8_t m_buffer[BUFFER_SIZE] = {0}; // Frame buffer
	bool m_is_enabled;
	I2C_HandleTypeDef* m_i2c_handler;

	Status_t WriteCommandByte(uint8_t byte);
	Status_t WriteCommand(CMD cmd);
	Status_t WriteCommandBytes(uint8_t* buffer, size_t buffer_size);
	Status_t WriteData(uint8_t* buffer, size_t buff_size);
	Status_t SetDisplayEnable(bool enable);


};

#endif /* DISPLAY_SSD1306_SSD1306_H_ */


