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

bool HabitManager::ToggleHabit(size_t index)
{
	if (index >= m_count)
	{
		return false;
	}

	Habit_t habit = m_habits[index];

	if (habit.IsComplete)
	{
		habit.IsComplete = false;
		habit.Streak--;
	}else
	{
		habit.IsComplete = true;
		habit.Streak++;
	}

	m_habits[index] = habit;

	return true;
}

void HabitManager::Reset()
{
	Habit_t habit;
	for (size_t i = 0; i < m_count; i++)
	{
		habit = m_habits[i];
		if (!habit.IsComplete)
		{
			habit.Streak = 0;
		}
		habit.IsComplete = false;
		m_habits[i] = habit;
	}
}
