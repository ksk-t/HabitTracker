/*
 * HabitManager.h
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#ifndef SRC_HABITMANAGER_H_
#define SRC_HABITMANAGER_H_

#include <array>

// Command Codes
#define HABIT_MANAGER_CMD_RESET 0
#define HABIT_MANAGER_CMD_ADD_HABIT 1

// Constants
constexpr size_t MAX_RECORD_DAYS = 31;
constexpr size_t MAX_NUM_HABITS = 10;

class HabitManager
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
    * @param Return true on success, false otherwise
    */
   bool ToggleHabit(size_t index, uint8_t day);

   /*
    * Resets all habits to incomplete
    */
   void Reset();

   /*
    * Returns the habit count
    *
    * @Return Number of habits
    */
   size_t Count() { return MAX_NUM_HABITS; };

   /*
    * Gets the number of completion status recorded per habit
    */
   size_t RecordLength() { return MAX_RECORD_DAYS; };

private:
   std::array<std::array<bool, MAX_RECORD_DAYS>, MAX_NUM_HABITS> m_habits;
};


#endif
