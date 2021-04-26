/*
 * BasicTimer.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: keisu
 */

#include "BasicTimer.h"

void BasicTimer::Start(uint32_t initial_tick, uint32_t interval)
{
   m_initial_tick = initial_tick;
   m_interval = interval;
}

bool BasicTimer::HasExpired(uint32_t tick)
{
   return tick - m_initial_tick >= m_interval;
}
