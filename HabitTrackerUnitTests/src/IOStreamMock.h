/*
 * IOStreamMoch.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef IOSTREAMMOCH_H_
#define IOSTREAMMOCH_H_

#include "IOStreamBase.h"
#include <array>

class IOStreamMock : public IOStreamBase
{
public:
	size_t Read(uint8_t* buffer, size_t size) override;
	size_t Write(uint8_t* buffer, size_t size) override {return 0;};

	void WriteReadBuffer(uint8_t* buffer, size_t size);
private:
	std::array<uint8_t, 128> m_buffer;
	size_t m_size;
};


#endif /* IOSTREAMMOCH_H_ */
