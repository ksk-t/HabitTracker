/*
 * WS2812.h
 *
 *  Created on: May 3, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_WS2812_H_
#define EXTERNALPERIPHERALS_WS2812_H_

#include "Color.h"
#include "stm32f2xx_hal.h"
#include <cstddef>

class WS2812
{
public:
	WS2812(TIM_HandleTypeDef* timer_handle) : m_timer_handle(timer_handle) {};
    /*
     * Sets the color of a specified LED
     */
    void SetColor(size_t led, const Color_t color);

    /*
     * Updates LED colors
     */
    void Update();
private:
    TIM_HandleTypeDef* m_timer_handle;
    void ColorsToBytes();
};



#endif /* EXTERNALPERIPHERALS_WS2812_H_ */
