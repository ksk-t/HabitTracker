/*
 * Date.h
 *
 *  Created on: Apr 4, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_DATE_H_
#define EXTERNALPERIPHERALS_DATE_H_

enum class WeekDay_t
{
   Monday,
   Tuesday,
   Wednesday,
   Thursday,
   Friday,
   Saturday,
   Sunday
};

enum class Month_t
{
   Janurary,
   February,
   March,
   April,
   May,
   June,
   July,
   August,
   September,
   October, 
   November,
   December
};

struct Date_t
{
   uint32_t Year;
   uint8_t Day;
   WeekDay_t Weekday;
   Month_t Month;
};



#endif /* EXTERNALPERIPHERALS_DATE_H_ */
