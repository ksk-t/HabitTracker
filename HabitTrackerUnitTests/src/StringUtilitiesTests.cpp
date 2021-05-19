/*
 * StringUtilitiesTests.cpp
 *
 *  Created on: May 19, 2021
 *      Author: keisu
 */



#include "StringUtilities.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(StringUtilitiesTests)
{
};

TEST(StringUtilitiesTests, split_no_errors)
{
	std::string test_string = "125:6089:0912";
	const uint32_t buffer_size = 3;
	uint32_t output_buffer[buffer_size] = {0};
	LONGS_EQUAL(3, StringUtilities::SplitToUint(test_string, ':', output_buffer, buffer_size));
	LONGS_EQUAL(125, output_buffer[0]);
	LONGS_EQUAL(6089, output_buffer[1]);
	LONGS_EQUAL(912, output_buffer[2]);
}

TEST(StringUtilitiesTests, split_errors)
{
	// Non numeric character in first partition
	std::string test_string = "A125:6089:0912";
	const uint32_t buffer_size = 3;
	uint32_t output_buffer[buffer_size] = {0};
	LONGS_EQUAL(0, StringUtilities::SplitToUint(test_string, ':', output_buffer, buffer_size));

	// Non numeric character in second partition
	test_string = "123:A123:123";
	LONGS_EQUAL(1, StringUtilities::SplitToUint(test_string, ':', output_buffer, buffer_size));
	LONGS_EQUAL(123, output_buffer[0]);

	// Empty partition
	test_string = ":123:123";
	LONGS_EQUAL(0, StringUtilities::SplitToUint(test_string, ':', output_buffer, buffer_size));

	// Empty string
	test_string = "";
	LONGS_EQUAL(0, StringUtilities::SplitToUint(test_string, ':', output_buffer, buffer_size));

	// Buffer too small
	test_string = "123:123:123";
	LONGS_EQUAL(2, StringUtilities::SplitToUint(test_string, ':', output_buffer, 2));
}

