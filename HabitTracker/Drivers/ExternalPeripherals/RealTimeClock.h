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
#include "CommandCallableBase.h"

#define TIME_CMD_SET_TIME 0

class RealTimeClock : public CommandCallableBase
{
public:
   RealTimeClock(RTC_HandleTypeDef* handle) : m_handle(handle) {};
   void Initialize();
   Time_t GetTime();
   void SetTime(Time_t time);
   cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream);
private:
   RTC_HandleTypeDef* m_handle;
};


#endif /* EXTERNALPERIPHERALS_REALTIMECLOCK_H_ */
