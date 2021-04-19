/*
 * IOStreamMock.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#include "IOStreamMock.h"


void IOStreamMock::WriteReadBuffer(uint8_t* buffer, size_t size)
{
	size_t index;
	for (index = 0; index < size && index < m_buffer.size(); index++)
	{
		m_buffer[index] = buffer[index];
	}

	m_size = index;
}

size_t IOStreamMock::Read(uint8_t* buffer, size_t size)
{
	size_t index;
	for (index = 0; index < size && index < m_size; index++)
	{
		buffer[index] = m_buffer[index];
	}

	return index;
}
