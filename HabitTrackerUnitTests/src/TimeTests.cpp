/*
 * RealTimeClockUtilitiesTest.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: keisu
 *
 *  Description: Tests for RealTimeClockUtiltis
 */



#include "Time.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(TimeTests)
{

};


TEST(TimeTests, default_values)
{
	Time_t time;
	LONGS_EQUAL(12, time.Hours);
	LONGS_EQUAL(0, time.Minutes);
	LONGS_EQUAL(0, time.Seconds);
	CHECK(TimeFormat_t::Format_12_AM == time.TimeFormat);
	CHECK(DayLightSaving_t::None == time.DayLightSaving);
	CHECK(StoreOperation_t::Reset == time.StoreOperation);
}

TEST(TimeTests, to_string_test_no_colon_toggle)
{
	Time_t time;
	STRCMP_EQUAL("12:00AM", time.ToString().c_str());
   
   time.Hours = 4;
   time.Minutes = 32;
   time.TimeFormat = TimeFormat_t::Format_12_PM;
	STRCMP_EQUAL("4:32PM", time.ToString().c_str());
}

TEST(TimeTests, to_string_test_colon_toggle)
{
	Time_t time;
	STRCMP_EQUAL("12:00AM", time.ToString(true).c_str());

   time.Seconds = 1;
	STRCMP_EQUAL("12 00AM", time.ToString(true).c_str());
}

TEST(TimeTests, from_string)
{
	Time_t time;
	CHECK(time.FromString("5:43PM"));
	LONGS_EQUAL(5, time.Hours);
	LONGS_EQUAL(43, time.Minutes);
	CHECK(time.TimeFormat == TimeFormat_t::Format_12_PM);

	CHECK(time.FromString("12:30AM"));
	LONGS_EQUAL(12, time.Hours);
	LONGS_EQUAL(30, time.Minutes);
	CHECK(time.TimeFormat == TimeFormat_t::Format_12_AM);
}

TEST(TimeTests, from_string_invalid_input)
{
	Time_t time;
	CHECK_FALSE(time.FromString("124:34AM"));
	CHECK_FALSE(time.FromString("12z:34AM"));
	CHECK_FALSE(time.FromString("z12:34AM"));
	CHECK_FALSE(time.FromString("12:z34AM"));
	CHECK_FALSE(time.FromString("12:34zAM"));
	CHECK_FALSE(time.FromString("12:345AM"));
}
