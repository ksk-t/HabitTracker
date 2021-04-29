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
	return m_habits.size();
}

bool HabitManager::AddHabit(Habit_t habit)
{
	if (m_count >= m_habits.size())
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
	for (Habit_t &habit : m_habits)
	{
		if (!habit.IsComplete)
		{
			habit.Streak = 0;
		}
		habit.IsComplete = false;
	}
}

cmd_status_t HabitManager::CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream)
{
	switch(code)
	{
	case HABIT_MANAGER_CMD_RESET:
	{
		Reset();
		uint8_t msg[] = "Habit manager has been reset";
		iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
		break;
	}
	case HABIT_MANAGER_CMD_ADD_HABIT:
	{
		if (size > 0)
		{
			Habit_t habit;
			for (size_t i = 0; i < size; i++)
			{
				habit.Name += (char)buffer[i];
			}
			if (AddHabit(habit))
			{
				uint8_t msg[] = "Habit added";
				iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
			}else
			{
				uint8_t msg[] = "FAILED TO ADD HABIT";
				iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
			}
		}else
		{
			uint8_t msg[] = "FAILED TO ADD HABIT: Empty name string";
			iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
		}

		break;
	}
	default:
		return cmd_status_t::InvalidCode;
	}

	return cmd_status_t::Ok;
}
