/*
 * RotaryEncoderTests.cpp
 *
 *  Created on: Apr 12, 2021
 *      Author: keisu
 */


#include "RotaryEncoder.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(RotaryEncoderTests)
{
	RotaryEncoder *encoder;
	const uint32_t initial_pos = 0;
	void setup()
	{
		encoder = new RotaryEncoder(initial_pos);
	}

	void teardown()
	{
		delete encoder;
	}
};

TEST(RotaryEncoderTests, no_movement)
{
	CHECK_FALSE(encoder->HasMoved(0));
	CHECK_FALSE(encoder->HasMoved(1));
	CHECK_FALSE(encoder->HasMoved(65535));
}

TEST(RotaryEncoderTests, movement_no_overflow)
{
	CHECK(encoder->HasMoved(2));
}

TEST(RotaryEncoderTests, movement_with_overflow)
{
	CHECK(encoder->HasMoved(65534));
}

TEST(RotaryEncoderTests, movement_after_no_movement)
{
	CHECK(encoder->HasMoved(2));
	CHECK_FALSE(encoder->HasMoved(2));
	CHECK(encoder->HasMoved(0));
}



