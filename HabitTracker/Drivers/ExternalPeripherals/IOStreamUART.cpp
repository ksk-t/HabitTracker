/*
 * IOStreamUART.cpp
 *
 *  Created on: Apr 22, 2021
 *      Author: keisu
 */

#include "IOStreamUART.h"

IOStreamUART::IOStreamUART(UART_HandleTypeDef* uart_handle) :
   m_uart_handle(uart_handle),
   m_read_offset(0)
{
	Reset();
}

size_t IOStreamUART::Read(uint8_t* buffer, size_t size)
{
   size_t bytes_read = 0;

   // Fill read buffer with available data
   while ((bytes_read < size) && (bytes_read < m_bytes_available))
   {
      buffer[bytes_read] = m_rx_interrupt_buffer[bytes_read];
      bytes_read++;
   }

   Reset();

   return bytes_read;
}

size_t IOStreamUART::Write(uint8_t* buffer, size_t size)
{
	HAL_UART_Transmit(m_uart_handle, buffer, size,0xffff);
	return size;
}

size_t IOStreamUART::BytesAvailable()
{
	while (m_bytes_available < RX_INTERRUPT_BUFFER_SIZE && m_rx_interrupt_buffer[m_bytes_available])
	{
		m_bytes_available++;
	}

   return m_bytes_available;
}

bool IOStreamUART::IsRxBufferFull()
{
	return m_bytes_available == RX_INTERRUPT_BUFFER_SIZE;
}

bool IOStreamUART::Peak(size_t index, uint8_t &value)
{
   if (index < m_bytes_available)
   {
      value = m_rx_interrupt_buffer[index];
      return true;
   }else
   {
      return false;
   }
}

void IOStreamUART::Reset()
{
	std::fill_n(m_rx_interrupt_buffer, RX_INTERRUPT_BUFFER_SIZE, 0);
	m_bytes_available = 0;

	HAL_UART_Abort_IT(m_uart_handle);
	HAL_UART_Receive_IT(m_uart_handle, m_rx_interrupt_buffer, RX_INTERRUPT_BUFFER_SIZE);
}

void IOStreamUART::TransmitStartChars()
{
	uint8_t start_chars[] = "\n\r>";
	HAL_UART_Transmit(m_uart_handle, start_chars, sizeof(start_chars) / sizeof(start_chars[0]), 0xffff);
}
