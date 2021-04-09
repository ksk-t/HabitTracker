/*
 * HabitManager.h
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#ifndef SRC_HABITMANAGER_H_
#define SRC_HABITMANAGER_H_


#include "Habit.h"

class HabitManager
{
public:
   bool AddHabit(Habit_t habit);
   bool GetHabit(size_t index, Habit_t &habit);
   size_t Count();
   size_t MaxCount();
private:
   static const size_t MAX_COUNT{10};
   Habit_t m_habits[MAX_COUNT];
   size_t m_count{0};
};


#endif
