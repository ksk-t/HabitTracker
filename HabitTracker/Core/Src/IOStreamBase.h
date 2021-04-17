/*
 * IOStream.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef SRC_IOSTREAMBASE_H_
#define SRC_IOSTREAMBASE_H_

#include <cstdint>
#include <cstddef>

class IOStreamBase
{
public:
	// Reads data from stream and copies data to buffer
	//
	// @param buffer Buffer to write the read data to
	// @param size of the buffer
	// @return Number of bytes actually read
	virtual size_t Read(uint8_t* buffer, size_t size) {return 0;};

	// Write data stream
	//
	// @param buffer Buffer containing data to write
	// @param size Size of buffer
	// @return number of bytes actually written
	virtual size_t Write(uint8_t* buffer, size_t size) {return 0;};
};


#endif /* SRC_IOSTREAM_H_ */
