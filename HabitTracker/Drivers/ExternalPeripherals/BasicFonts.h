/*
 * BasicFont.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_BASICFONTS_H_
#define EXTERNALPERIPHERALS_BASICFONTS_H_

#include <cstdint>

struct BasicFont{
	const uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
};

#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#ifdef SSD1306_INCLUDE_FONT_6x8
extern BasicFont Font_6x8;
#endif
#ifdef SSD1306_INCLUDE_FONT_7x10
extern BasicFont Font_7x10;
#endif
#ifdef SSD1306_INCLUDE_FONT_11x18
extern BasicFont Font_11x18;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x26
extern BasicFont Font_16x26;
#endif



#endif /* EXTERNALPERIPHERALS_BASICFONTS_H_ */
