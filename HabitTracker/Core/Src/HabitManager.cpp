/*
 * HabitManager.cpp
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#include "HabitManager.h"

size_t HabitManager::Count()
{
	return m_count;
}

size_t HabitManager::MaxCount()
{
	return MAX_COUNT;
}

bool HabitManager::AddHabit(Habit_t habit)
{
	if (m_count >= MAX_COUNT)
	{
		return false;
	}

	m_habits[m_count++] = habit;
	return true;
}

bool HabitManager::GetHabit(size_t index, Habit_t &habit)
{
	if (index >= m_count)
	{
		return false;
	}

	habit = m_habits[index];
	return true;
}
