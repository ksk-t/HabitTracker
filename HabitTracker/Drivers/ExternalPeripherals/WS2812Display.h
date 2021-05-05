/*
 * WS2812Display.h
 *
 *  Created on: May 4, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_WS2812DISPLAY_H_
#define EXTERNALPERIPHERALS_WS2812DISPLAY_H_

#include "Display.h"
#include "WS2812.h"

class WS2812Display : public Display
{
public:
	WS2812Display(WS2812* led_strip) : m_led_strip(led_strip) {};
   Status_t Initialize() override;
   Status_t DrawPixel(Point_t point, Color_t color) override;
   uint32_t GetHeight() override;
   uint32_t GetWidth() override;
   Status_t Update() override;
private:
	WS2812* m_led_strip;

   const static uint32_t HEIGHT = 8;
   const static uint32_t WIDTH = 32;
};



#endif /* EXTERNALPERIPHERALS_WS2812DISPLAY_H_ */
