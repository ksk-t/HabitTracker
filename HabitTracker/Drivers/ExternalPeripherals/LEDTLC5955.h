/*
 * LEDTLC5955.h
 *
 *  Created on: Jun 2, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_LEDTLC5955_H_
#define EXTERNALPERIPHERALS_LEDTLC5955_H_

#include "stm32f2xx_hal.h"
#include "Color.h"

#define TLC5955_COMMON_BUFFER_SIZE 97

struct TLC5955_function_t
{
	bool auto_display_repeat = false;
	bool display_timing_reset_enable = false;
	bool auto_data_refresh = false;
	bool es_pwm_enable = false;
	bool lsd_detection_voltage = false;
};

class LEDTLC5955
{
public:
   /* Constructor */
   LEDTLC5955();
   
   /*
    * Sets the configuration settings
    *
    * @param config configuration settings
    */
   void SetFunction(TLC5955_function_t function);

   void SetDotCorrection(uint32_t led_index, uint8_t r_dc, uint8_t g_dc, uint8_t b_dc);

   void SetMaxCurrent(uint8_t r_mc, uint8_t g_mc, uint8_t b_mc);

   void SetGlobalBrightness(uint8_t r_gb, uint8_t g_gb, uint8_t b_gb);

   void UpdateControlSettings();
   /* 
    * Sets the color of the specified LED. A call to Update() is required
    * for the changes made by this function to take place
    *
    * @param led_index Index of the LED to change the color of
    * @param color Color to change the LED to
    */
   void SetLed(uint32_t led_index, Color_t color);
   
   /*
    * Turns all LEDs off. A call to Update() is required for the changes made 
    * by this function to take place
    */
   void Clear();
   
   /*
    * Updates LED
    */
   void UpdateLED();
private:
   const static uint32_t LED_COUNT = 16;

   uint8_t m_gs_buffer[TLC5955_COMMON_BUFFER_SIZE];
   uint8_t m_control_buffer[TLC5955_COMMON_BUFFER_SIZE];

   void set_value(uint8_t* buffer, size_t buffer_size, uint32_t bit, uint32_t value, uint8_t value_size);
   void set_bit(uint8_t* buffer, size_t buffer_size, uint32_t index, bool set_bit);
};


#endif /* EXTERNALPERIPHERALS_LEDTLC5955_H_ */
