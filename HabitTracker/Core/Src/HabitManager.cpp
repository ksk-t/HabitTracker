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

bool HabitManager::ToggleHabit(size_t index, uint8_t day)
{
	return true;
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
