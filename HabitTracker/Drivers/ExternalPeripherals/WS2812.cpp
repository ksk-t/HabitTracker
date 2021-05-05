/*
 * WS2812.cpp
 *
 *  Created on: May 3, 2021
 *      Author: keisu
 */

#include "WS2812.h"

extern TIM_HandleTypeDef htim3;

// Timer parameters
const static uint16_t BIT_VALUE_0  = 21; // This is specific to a 16 Mhz timer
const static uint16_t BIT_VALUE_1  = 42; // This is specific to a 16 Mhz timer

const static uint8_t NUM_BITS_PER_LED = 24;
const static size_t NUM_LEDS = 512;
const static size_t BUFFER_SIZE = NUM_LEDS * NUM_BITS_PER_LED + 2; // 2 for the reset signal
static uint16_t _write_buffer[BUFFER_SIZE] = {0};
static Color_t _colors_new[NUM_LEDS];


void WS2812::SetColor(size_t led, const Color_t color)
{
	if (led < NUM_LEDS)
	{
		_colors_new[led] = color;
	}
}

void WS2812::ColorsToBytes()
{
    for(uint32_t i = 0; i < NUM_LEDS; i++)
    {
    	for (uint8_t k = 0; k < 8; k++) // For each bit in each color
        {
            _write_buffer[i * NUM_BITS_PER_LED + k     ] = (( _colors_new[i].G << k) & 0x80) == 0 ? BIT_VALUE_0 : BIT_VALUE_1;
            _write_buffer[i * NUM_BITS_PER_LED + k + 8 ] = (( _colors_new[i].R << k) & 0x80) == 0 ? BIT_VALUE_0 : BIT_VALUE_1;
            _write_buffer[i * NUM_BITS_PER_LED + k + 16] = (( _colors_new[i].B << k) & 0x80) == 0 ? BIT_VALUE_0 : BIT_VALUE_1;
        }
    }

    // Reset signal
    _write_buffer[BUFFER_SIZE - 2] = 0;
    _write_buffer[BUFFER_SIZE - 1] = 0;
}

void WS2812::Update()
{
	HAL_TIM_PWM_Stop_DMA(m_timer_handle, TIM_CHANNEL_2);

    ColorsToBytes();
    HAL_TIM_PWM_Start_DMA(m_timer_handle, TIM_CHANNEL_2, (uint32_t*)_write_buffer, BUFFER_SIZE);
}

