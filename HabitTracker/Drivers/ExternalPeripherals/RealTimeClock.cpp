/*
 * RealTimeClock.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: keisu
 *
 *  Note: Cannot call logger since the logger depends on this 
 */

#include "RealTimeClock.h"

static const std::string MODULE_NAME = "RealTimeClock";

void RealTimeClock::Initialize()
{
   if (m_handle == nullptr)
   {
      return;
   }

	RTC_DateTypeDef date_structure;
   RTC_TimeTypeDef time_structure; 

	// Configure Date
	date_structure.Year = 0;
   date_structure.Month = RTC_MONTH_FEBRUARY;
	date_structure.Date = 1;
   date_structure.WeekDay = RTC_WEEKDAY_TUESDAY;
   HAL_RTC_SetDate(m_handle ,&date_structure , RTC_FORMAT_BIN);

   // Configure Time
   time_structure.Hours = 12;
   time_structure.Minutes = 59;
   time_structure.Seconds = 55;
   time_structure.TimeFormat = RTC_HOURFORMAT12_PM;
   time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
   time_structure.StoreOperation = RTC_STOREOPERATION_RESET;
   HAL_RTC_SetTime(m_handle, &time_structure, RTC_FORMAT_BIN);
}

Time_t RealTimeClock::GetTime()
{
   RTC_TimeTypeDef time;
   RTC_DateTypeDef date;
   HAL_RTC_GetTime(m_handle, &time, RTC_FORMAT_BIN);
   HAL_RTC_GetDate(m_handle, &date, RTC_FORMAT_BIN); // Must be called after getting time to unlock higher order calander shadow registers

   Time_t ret_time;
   ret_time.Hours = time.Hours;
   ret_time.Minutes = time.Minutes;
   ret_time.Seconds = time.Seconds;

   switch(time.TimeFormat)
   {
   case RTC_HOURFORMAT12_AM:
	   ret_time.TimeFormat = TimeFormat_t::Format_12_AM;
	   break;
   case RTC_HOURFORMAT12_PM:
	   ret_time.TimeFormat = TimeFormat_t::Format_12_PM;
   	   break;
   }

   switch(time.DayLightSaving)
   {
   case RTC_DAYLIGHTSAVING_SUB1H:
	   ret_time.DayLightSaving = DayLightSaving_t::Sub_1H;
	   break;
   case RTC_DAYLIGHTSAVING_ADD1H:
	   ret_time.DayLightSaving = DayLightSaving_t::Add_1H;
	   break;
   case RTC_DAYLIGHTSAVING_NONE:
	   ret_time.DayLightSaving = DayLightSaving_t::None;
	   break;
   }

   switch(time.StoreOperation)
   {
   case RTC_STOREOPERATION_RESET:
	   ret_time.StoreOperation = StoreOperation_t::Reset;
	   break;
   case RTC_STOREOPERATION_SET:
	   ret_time.StoreOperation = StoreOperation_t::Set;
	   break;
   }

   return ret_time;
}

void RealTimeClock::SetTime(Time_t time)
{
   RTC_TimeTypeDef time_structure;

   // Configure Time
   time_structure.Hours = time.Hours;
   time_structure.Minutes = time.Minutes;
   time_structure.Seconds = time.Seconds;
   switch(time.TimeFormat)
   {
   case TimeFormat_t::Format_12_AM:
	   time_structure.TimeFormat = RTC_HOURFORMAT12_AM;
	   break;
   case TimeFormat_t::Format_12_PM:
	   time_structure.TimeFormat = RTC_HOURFORMAT12_PM;
	   break;
   }
   switch(time.DayLightSaving)
   {
   case DayLightSaving_t::Sub_1H:
	   time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_SUB1H;
	   break;
   case DayLightSaving_t::Add_1H:
	   time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_ADD1H;
	   break;
   case  DayLightSaving_t::None:
	   time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	   break;
   }
   switch(time.StoreOperation)
   {
   case StoreOperation_t::Reset:
	   time_structure.StoreOperation = RTC_STOREOPERATION_RESET;
	   break;
   case StoreOperation_t::Set:
   	   time_structure.StoreOperation = RTC_STOREOPERATION_SET;
	   break;
   }

   HAL_RTC_SetTime(m_handle, &time_structure, RTC_FORMAT_BIN);
}

cmd_status_t RealTimeClock::CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream)
{
	switch(code)
	{
	case TIME_CMD_SET_TIME:
	{
		std::string time_string((char*)buffer, size - 1); // Buffer includes \r character. - 1 to remove it
		Time_t new_time;
		if (new_time.FromString(time_string))
		{
			SetTime(new_time);
			return cmd_status_t::Ok;
		}else
		{
			return cmd_status_t::InvalidParamter;
		}
		break;
	}
	default:
		return cmd_status_t::InvalidCode;
	}


}

