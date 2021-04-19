/*
 * IOStreamMockTests.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */


#include "IOStreamMock.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


TEST_GROUP(IOStreamMockTests)
{
	IOStreamMock *iostream;
	void setup()
	{
		iostream = new IOStreamMock();
	}

	void teardown()
	{
		delete iostream;
	}
};

TEST(IOStreamMockTests, write_to_read_buffer)
{
	const size_t buffer_size = 20;
	uint8_t readbuffer[buffer_size] = "testvalue";
	uint8_t receivebuffer[buffer_size] = {0};

	iostream->WriteReadBuffer(readbuffer, 10);
	LONGS_EQUAL(10, iostream->Read(receivebuffer, buffer_size));
	MEMCMP_EQUAL(readbuffer, receivebuffer, 10);
}
