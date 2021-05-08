/*
 * HabitManager.cpp
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#include "HabitManager.h"

HabitManager::HabitManager()
{
	Reset();
}

bool HabitManager::GetHabitStatus(size_t id, uint8_t day)
{
	if (id < MAX_NUM_HABITS && day < MAX_RECORD_DAYS)
	{
		return m_habits[id][day];
	}else
	{
		return false;
	}
}

bool HabitManager::ToggleHabit(size_t id, uint8_t day)
{
	if (id < MAX_NUM_HABITS && day < MAX_RECORD_DAYS)
	{
		m_habits[id][day] = !m_habits[id][day];
	}else
	{
		return false;
	}
}

void HabitManager::Reset()
{
	for (size_t i = 0; i < MAX_NUM_HABITS; i++)
	{
		for (size_t j = 0; j < MAX_RECORD_DAYS; j++)
		{
			m_habits[i][j] = false;
		}
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
	default:
		return cmd_status_t::InvalidCode;
	}

	return cmd_status_t::Ok;
}
