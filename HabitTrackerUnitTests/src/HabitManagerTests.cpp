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

TEST(HabitManagerTests, count_added_habit)
{
	Habit_t test_habit;

	LONGS_EQUAL(0,manager->Count());
	manager->AddHabit(test_habit);
	LONGS_EQUAL(1,manager->Count());
	manager->AddHabit(test_habit);
	LONGS_EQUAL(2,manager->Count());
}

TEST(HabitManagerTests, added_too_many)
{
	Habit_t test_habit;
	for (size_t i = 0; i < manager->MaxCount(); i++)
	{
		CHECK(manager->AddHabit(test_habit));
	}

	CHECK_FALSE(manager->AddHabit(test_habit));
}

TEST(HabitManagerTests, get_habit)
{
	Habit_t test_habit;
	test_habit.Name = "test name";
	test_habit.IsComplete = true;
	test_habit.Streak = 123;

	Habit_t habit;
	manager->AddHabit(test_habit);
	CHECK(manager->GetHabit(0, habit));
	STRCMP_EQUAL("test name", habit.Name.c_str());
	CHECK(habit.IsComplete);
	LONGS_EQUAL(123, habit.Streak);

	test_habit.Name = "test name2";
	test_habit.IsComplete = false;
	test_habit.Streak = 321;
	manager->AddHabit(test_habit);
	CHECK(manager->GetHabit(1, habit));
	STRCMP_EQUAL("test name2", habit.Name.c_str());
	CHECK_FALSE(habit.IsComplete);
	LONGS_EQUAL(321, habit.Streak);
}

TEST(HabitManagerTests, get_habit_out_of_range)
{
	Habit_t habit;
	CHECK_FALSE(manager->GetHabit(0, habit));
}

TEST(HabitManagerTests, toggle_habit_completion)
{
	Habit_t test_habit;
	test_habit.Name = "test name";
	test_habit.IsComplete = true;
	test_habit.Streak = 123;
	manager->AddHabit(test_habit);
	manager->ToggleHabit(0);
	manager->GetHabit(0, test_habit);
	CHECK_FALSE(test_habit.IsComplete);
	LONGS_EQUAL(122, test_habit.Streak);
	manager->ToggleHabit(0);
	manager->GetHabit(0, test_habit);
	CHECK(test_habit.IsComplete);
	LONGS_EQUAL(123, test_habit.Streak);
}
