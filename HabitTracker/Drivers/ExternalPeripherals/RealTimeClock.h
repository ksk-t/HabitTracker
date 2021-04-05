/*
 * RealTimeClock.h
 *
 *  Created on: Apr 4, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_REALTIMECLOCK_H_
#define EXTERNALPERIPHERALS_REALTIMECLOCK_H_

#include "stm32f2xx_hal.h"
#include "Time.h"

class RealTimeClock
{
public:
   RealTimeClock(RTC_HandleTypeDef* handle) : m_handle(handle) {};
   void Initialize();
   Time_t GetTime();
private:
   RTC_HandleTypeDef* m_handle;
};


#endif /* EXTERNALPERIPHERALS_REALTIMECLOCK_H_ */
