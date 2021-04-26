/*
 * BasicTimerTests.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: keisu
 */


#include "BasicTimer.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(BasicTimerTests)
{
	BasicTimer* timer;

	void setup()
	{
		timer = new BasicTimer();
	}

	void teardown()
	{
		delete timer;
	}
};

TEST(BasicTimerTests, time_not_expired)
{
   timer->Start(0, 10);
   CHECK_FALSE(timer->HasExpired(9));

   timer->Start(10, 10);
   CHECK_FALSE(timer->HasExpired(19));
}

TEST(BasicTimerTests, time_expired)
{
   timer->Start(0, 10);
   CHECK(timer->HasExpired(10));
}

TEST(BasicTimerTests, time_not_expired_overflow)
{
   timer->Start(UINT32_MAX, 10);
   CHECK_FALSE(timer->HasExpired(5));
}

TEST(BasicTimerTests, time_expired_overflow)
{
   timer->Start(UINT32_MAX, 10);
   CHECK(timer->HasExpired(10));
}
