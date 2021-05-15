/*
 * IOStreamUART.h
 *
 *  Created on: Apr 22, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_IOSTREAMUART_H_
#define EXTERNALPERIPHERALS_IOSTREAMUART_H_

#include "IOStreamBase.h"
#include "stm32f2xx_hal.h"

class IOStreamUART : public IOStreamBase
{
public:
   /*
    * Construtor
    */
   IOStreamUART(UART_HandleTypeDef* uart_handle);
	
   /*
    * Read data available in the receive buffer
    *
    * @param buffer Buffer to write the received data to
    * @param size Size size of buffer
    *
    * @return numbers of bytes actually read
    */
   size_t Read(uint8_t* buffer, size_t size) override;

   /*
    * Write data to the io stream
    *
    * @param buffer Buffer containing data to write to io stream
    * @param size Number of bytes in buffer
    *
    * @return Number of bytes written
    */
   size_t Write(uint8_t* buffer, size_t size) override;

   /*
    * Peak at a certain value in the receive buffer
    *
    * @param index Index of the value to peak
    * @param value Value of the element at index
    * 
    * @return True on success, false otherwise 
    */
   bool Peak(size_t index, uint8_t &value);
      
   /*
    * Returns the number of bytes availabe in the read buffer
    *
    * @return number of bytes in the read buffer
    */
   size_t BytesAvailable();

   /*
    * Determines if the receive buffer is full
    *
    * @param Returns true if the receive buffer is full, false otherwise
    */
   bool IsRxBufferFull();

   /*
    * Set up UART to receive input
    */
   void TransmitStartChars();

   /*
    * Clears buffer and request additional data from UART port
    */
   void Reset();

private:
   UART_HandleTypeDef* m_uart_handle; 
   size_t m_read_offset;

};


#endif /* EXTERNALPERIPHERALS_IOSTREAMUART_H_ */
