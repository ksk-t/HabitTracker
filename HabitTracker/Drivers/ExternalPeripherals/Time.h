/*
 * Time.h
 *
 *  Created on: Apr 4, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_TIME_H_
#define EXTERNALPERIPHERALS_TIME_H_

#include <cstdint>
#include <string>

enum class TimeFormat_t
{
   Format_12_AM,
   Format_12_PM
};

enum class DayLightSaving_t
{
   Sub_1H,
   Add_1H,
   None
};

enum class StoreOperation_t
{
   Reset,
   Set
};

struct Time_t
{
   uint8_t Hours{12};
   uint8_t Minutes{0};
   uint8_t Seconds{0};
   TimeFormat_t TimeFormat{TimeFormat_t::Format_12_AM};
   DayLightSaving_t DayLightSaving{DayLightSaving_t::None};
   StoreOperation_t StoreOperation{StoreOperation_t::Reset};
   std::string ToString(bool toggle_colon = false);
};

#endif /* EXTERNALPERIPHERALS_TIME_H_ */
