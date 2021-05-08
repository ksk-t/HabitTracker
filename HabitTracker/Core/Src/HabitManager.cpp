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
		return true;
	}else
	{
		return false;
	}
}

bool HabitManager::ToggleHabit(std::string str)
{
	std::string str_partition;
	std::string::iterator iter = str.begin();
	size_t id = 0;
	size_t day = 0;

	if (!isdigit(*iter))
	{
		return false;
	}
	while (isdigit(*iter) && iter != str.end())
	{
	   str_partition += *iter;
	   iter++;
	}
	id = std::stoi(str_partition);

	iter++; // Skip the "," character
	str_partition = "";
	if (!isdigit(*iter))
	{
		return false;
	}
	while (isdigit(*iter) && iter != str.end())
	{
	   str_partition += *iter;
	   iter++;
	}

	day = std::stoi(str_partition);

	return ToggleHabit(id, day);
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
	case HABIT_MANAGER_CMD_TOGGLE:
	{
		std::string str((char*)buffer, size - 1); // - 1 to remove \r
		if (ToggleHabit(str))
		{
			uint8_t msg[] = "Habit toggled";
			iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
		}else
		{
			uint8_t msg[] = "Invalid habit";
			iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
		}
	}
	default:
		return cmd_status_t::InvalidCode;
	}

	return cmd_status_t::Ok;
}
