/*
 * Habit.h
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#ifndef SRC_HABITS_H_
#define SRC_HABITS_H_

#include <string>
#include <cstdint>

struct Habit_t
{
	std::string Name;
   bool IsComplete;
   uint32_t Streak;
};

#endif
