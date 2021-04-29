/*
 * HabitManager.h
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#ifndef SRC_HABITMANAGER_H_
#define SRC_HABITMANAGER_H_

#include "Habit.h"
#include "CommandCallableBase.h"
#include <array>

// Command Codes
#define HABIT_MANAGER_CMD_RESET 0
#define HABIT_MANAGER_CMD_ADD_HABIT 1

class HabitManager : public CommandCallableBase
{
public:
   bool AddHabit(Habit_t habit);
   bool GetHabit(size_t index, Habit_t &habit);
   bool ToggleHabit(size_t index);
   void Reset();
   size_t Count();
   size_t MaxCount();

   cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream);
private:
   std::array<Habit_t, 10> m_habits;
   size_t m_count{0};
};


#endif
