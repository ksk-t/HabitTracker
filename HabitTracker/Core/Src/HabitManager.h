/*
 * HabitManager.h
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#ifndef SRC_HABITMANAGER_H_
#define SRC_HABITMANAGER_H_

#include <array>
#include "CommandCallableBase.h"

// Command Codes
#define HABIT_MANAGER_CMD_RESET 0
#define HABIT_MANAGER_CMD_TOGGLE 1

// Constants
constexpr size_t MAX_RECORD_DAYS = 32;
constexpr size_t MAX_NUM_HABITS = 8;

class HabitManager : public CommandCallableBase
{
public:

	HabitManager();

	/*
	 * Return completion status of a habit on a given day
	 *
	 * @param id ID number of the habit to get the completion status of
	 * @param day Day to get the completion status of
	 *
	 * @return True if habit was complete, false otherwise
	 */
     bool GetHabitStatus(size_t id, uint8_t day);

   /*
    * Toggles the completion status of a habit
    *
    * @param id ID number of the habit to toggle
    * @param day Day to toggle
    *
    * @return Return true on success, false otherwise
    */
   bool ToggleHabit(size_t id, uint8_t day);

   /*
    * Toggles completion status of a habit identified by a string
    *
    * @param habit Habit identity as a string. Format: "<ID>,<DAY>"
    *
    * @return Returns true on success, false otherswise
    */
   bool ToggleHabit(std::string habit);
   /*
    * Resets all habits to incomplete
    */
   void Reset();

   /*
    * Returns the habit count
    *
    * @return Number of habits
    */
   size_t Count() { return MAX_NUM_HABITS; };

   /*
    * Gets the number of completion status recorded per habit
    *
    * @return Number of days recorded per habit
    */
   size_t RecordLength() { return MAX_RECORD_DAYS; };

   cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream);

private:
   std::array<std::array<bool, MAX_RECORD_DAYS>, MAX_NUM_HABITS> m_habits;
};


#endif
