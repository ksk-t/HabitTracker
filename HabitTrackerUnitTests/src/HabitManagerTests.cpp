/*
 * HabitManagerTests.cpp
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#include "HabitManager.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(HabitManagerTests)
{
	HabitManager* manager;
	void setup()
	{
		manager = new HabitManager();
	}

	void teardown()
	{
		delete manager;
	}
};

TEST(HabitManagerTests, initial_state)
{
	for (size_t i = 0; i < manager->Count(); i++)
	{
		for (size_t j = 0; j < manager->RecordLength(); j++)
		{
			CHECK_FALSE(manager->GetHabitStatus(i, j));
		}
	}
}

TEST(HabitManagerTests, toggle_habit)
{
	CHECK_FALSE(manager->GetHabitStatus(2, 3));
	manager->ToggleHabit(2, 3);
	CHECK(manager->GetHabitStatus(2, 3));
	manager->ToggleHabit(2, 3);
	CHECK_FALSE(manager->GetHabitStatus(2, 3));
	manager->ToggleHabit(2, 3);

}
