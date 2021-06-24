/* * LEDTLC5955.cpp * *  Created on: Jun 2, 2021
 *      Author: keisu
 */

#include "LEDTLC5955.h"
#include "FastPwmPin.h"
#include <SPI.h>


// Aurduino pin configuration
#define PIN_GSCLK 3
#define PIN_LAT   10
#define PIN_MOSI  11
#define PIN_SCLK  13

#define TLC5955_CONTROL_BIT (768)
#define TLC5955_CONTROL_BYTE (0x96)

#define TLC5955_AUTO_DISPLAY_REPEAT_BIT (366)
#define TLC5955_TIMING_RESET_BIT (367)
#define TLC5955_AUTO_DATA_REFRESH_BIT (368)
#define TLC5955_ES_PWM_BIT (369)
#define TLC5955_LSD_DETECTION_BIT (370)

#define TLC5955_BRIGHTNESS_DATA_SIZE (7)
#define TLC5955_RED_BRIGHTNESS_BIT (345)
#define TLC5955_GREEN_BRIGHTNESS_BIT (352)
#define TLC5966_BLUE_BRIGHTNESS_BIT (359)

#define TLC5955_MAX_CURRENT_DATA_SIZE (3)
#define TLC5955_RED_MAX_CURRENT_BIT (336)
#define TLC5955_GREEN_MAX_CURRENT_BIT (339)
#define TLC5966_BLUE_MAX_CURRENT_BIT (342)

static void spi_transfer(uint8_t* buffer, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    SPI.transfer(buffer[i]);
  }
}

static void latch()
{
  digitalWrite(PIN_LAT, HIGH);   // turn the LED on (HIGH is the voltage level)                // wait for a second
  digitalWrite(PIN_LAT, LOW);    // turn the LED off by making the voltage LOW
}

LEDTLC5955::LEDTLC5955()
{
	memset(m_gs_buffer, 0, TLC5955_COMMON_BUFFER_SIZE);
	memset(m_control_buffer, 0, TLC5955_COMMON_BUFFER_SIZE);

  // Initialize Pins
  pinMode(PIN_SCLK, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  digitalWrite(PIN_MOSI, LOW);
  pinMode(PIN_LAT, OUTPUT);
  digitalWrite(PIN_LAT, LOW);

  FastPwmPin::enablePwmPin(PIN_GSCLK, 4000000L, 50);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

void LEDTLC5955::SetFunction(TLC5955_function_t function)
{
   set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_AUTO_DATA_REFRESH_BIT, function.auto_data_refresh);
   set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_TIMING_RESET_BIT, function.display_timing_reset_enable);
   set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_AUTO_DISPLAY_REPEAT_BIT, function.auto_display_repeat);
   set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_ES_PWM_BIT, function.es_pwm_enable);
   set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_LSD_DETECTION_BIT, function.lsd_detection_voltage);
}

void LEDTLC5955::SetGlobalBrightness(uint8_t r_gb, uint8_t g_gb, uint8_t b_gb)
{
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_RED_BRIGHTNESS_BIT, r_gb, TLC5955_BRIGHTNESS_DATA_SIZE);
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_GREEN_BRIGHTNESS_BIT, g_gb, TLC5955_BRIGHTNESS_DATA_SIZE);
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5966_BLUE_BRIGHTNESS_BIT, b_gb, TLC5955_BRIGHTNESS_DATA_SIZE);
}

void LEDTLC5955::SetMaxCurrent(uint8_t r_mc, uint8_t g_mc, uint8_t b_mc)
{
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_RED_MAX_CURRENT_BIT, r_mc, TLC5955_MAX_CURRENT_DATA_SIZE);
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_GREEN_MAX_CURRENT_BIT, g_mc, TLC5955_MAX_CURRENT_DATA_SIZE);
	set_value(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5966_BLUE_MAX_CURRENT_BIT, b_mc, TLC5955_MAX_CURRENT_DATA_SIZE);
}

void LEDTLC5955::SetDotCorrection(uint32_t led_index,  uint8_t r_dc, uint8_t g_dc, uint8_t b_dc)
{

}

void LEDTLC5955::set_value(uint8_t* buffer, size_t buffer_size, uint32_t bit, uint32_t value, uint8_t value_size)
{
   uint8_t bits_written = 0;
   uint32_t bit_position = bit;
   while(bits_written < value_size && bit_position < buffer_size * 8)
   {
      set_bit(buffer, buffer_size, bit_position, (((value >> bits_written) & 0x01) == 0x01) ? true : false);
      bit_position++;
      bits_written++;
   }
}

void LEDTLC5955::set_bit(uint8_t* buffer, size_t buffer_size, uint32_t bit, bool set_bit)
{

   uint32_t index = (TLC5955_COMMON_BUFFER_SIZE - 1) - (bit / 8);
   uint8_t offset = bit % 8;
   
   if (index >= buffer_size)
   {
      return;
   }

   if (set_bit)
   {
      buffer[index] |= 0xff & (0x01 << offset); 
   }else
   {
      buffer[index] &= 0xff & (0xfe << offset);
   }

}

void LEDTLC5955::SetLed(uint32_t led_index, Color_t color)
{
   if (led_index >= LED_COUNT)
   {
      return;
   }

   uint32_t offset = (TLC5955_COMMON_BUFFER_SIZE - 1) - (led_index * 6);

   m_gs_buffer[offset] = 0xff & (color.R);
   m_gs_buffer[offset - 1] = 0xff & (color.R >> 8);
   m_gs_buffer[offset - 2] = 0xff & (color.G);
   m_gs_buffer[offset - 3] = 0xff & (color.G >> 8);
   m_gs_buffer[offset - 4] = 0xff & (color.B);
   m_gs_buffer[offset - 5] = 0xff & (color.B >> 8);
}

void LEDTLC5955::UpdateControlSettings()
{

	set_bit(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE, TLC5955_CONTROL_BIT, true);
	m_control_buffer[1] = TLC5955_CONTROL_BYTE;

  spi_transfer(m_control_buffer, TLC5955_COMMON_BUFFER_SIZE);
  latch();
}

void LEDTLC5955::UpdateLED()
{
     spi_transfer(m_gs_buffer, TLC5955_COMMON_BUFFER_SIZE);
     latch();
}

cmd_status_t LEDTLC5955::CommandCallback(uint8_t* buffer, size_t size, uint32_t code)
{
  m_gs_buffer[70] = 0xff;
  Serial.write("Here");
  return cmd_status_t::Ok;
}
