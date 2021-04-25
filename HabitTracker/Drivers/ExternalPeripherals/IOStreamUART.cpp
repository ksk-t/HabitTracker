/*
 * IOStreamUART.cpp
 *
 *  Created on: Apr 22, 2021
 *      Author: keisu
 */

#include "IOStreamUART.h"

static const size_t RX_BUFFER_SIZE = 128;
static uint8_t m_rx_buffer[RX_BUFFER_SIZE];
static const size_t RX_INTERRUPT_BUFFER_SIZE = 1;
static uint8_t m_rx_interrupt_buffer[RX_INTERRUPT_BUFFER_SIZE];
static volatile size_t m_bytes_available = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
   // Assume interrupt buffer is only one byte long
   if (m_bytes_available < RX_BUFFER_SIZE)
   {
      m_rx_buffer[m_bytes_available] = m_rx_interrupt_buffer[0];

      // Receive next byte
      HAL_UART_Receive_IT(huart, m_rx_interrupt_buffer, RX_INTERRUPT_BUFFER_SIZE);

      m_bytes_available++;
   }
}

IOStreamUART::IOStreamUART(UART_HandleTypeDef* uart_handle) :
   m_uart_handle(uart_handle),
   m_read_offset(0)
{
   std::fill_n(m_rx_buffer, RX_BUFFER_SIZE, 0);   

   HAL_UART_Receive_IT(m_uart_handle, m_rx_interrupt_buffer, RX_INTERRUPT_BUFFER_SIZE);
}

size_t IOStreamUART::Read(uint8_t* buffer, size_t size)
{
   size_t bytes_read = 0;

   // Fill read buffer with available data 
   while ((bytes_read < size) && (bytes_read + m_read_offset < m_bytes_available))
   {
      buffer[bytes_read] = m_rx_buffer[bytes_read + m_read_offset];
      bytes_read++;    
   }

   // Not enough space in buffer provided. User will need to call read again to get remaining data
   if (bytes_read >= size)
   {
	   m_read_offset = bytes_read;
   }else
   {
      HAL_UART_AbortReceive_IT(m_uart_handle);
      m_bytes_available = 0;
      HAL_UART_Receive_IT(m_uart_handle, m_rx_interrupt_buffer, RX_INTERRUPT_BUFFER_SIZE);
   }

   return bytes_read;
}

size_t IOStreamUART::Write(uint8_t* buffer, size_t size)
{
	HAL_UART_Transmit(m_uart_handle, buffer, size,0xffff);
	return size;
}

size_t IOStreamUART::BytesAvailable()
{
   return m_bytes_available;
}

bool IOStreamUART::Peak(size_t index, uint8_t &value)
{
   if (index < m_bytes_available)
   {
      value = m_rx_buffer[index];
      return true;
   }else
   {
      return false;
   }
}

void IOStreamUART::TransmitStartChars()
{
	uint8_t start_chars[] = "\n\r>";
	HAL_UART_Transmit(m_uart_handle, start_chars, sizeof(start_chars) / sizeof(start_chars[0]), 0xffff);
}
