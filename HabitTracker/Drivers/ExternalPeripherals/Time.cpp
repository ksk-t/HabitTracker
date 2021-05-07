/*
 * Time.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: keisu
 */


#include "Time.h"

std::string Time_t::ToString(bool toggle_colon) {
	std::string ret_str = "";

	ret_str += std::to_string(Hours);
	if (toggle_colon && Seconds % 2 == 1) {
		ret_str += " ";
	} else {
		ret_str += ":";
	}
	if (Minutes < 10) {
		ret_str += "0";
	}
	ret_str += std::to_string(Minutes);
	if (TimeFormat == TimeFormat_t::Format_12_AM) {
		ret_str += "AM";
	} else {
		ret_str += "PM";
	}

	return ret_str;
}

bool Time_t::FromString(std::string str)
{
	std::string str_partition;
	std::string::iterator iter = str.begin();
	// Get Hours
	if (!isdigit(*iter))
	{
		return false;
	}
   while (isdigit(*iter) && iter != str.end())
   {
	   str_partition += *iter;
	   iter++;
   }
   if (str_partition.length() > 2)
   {
	   return false;
   }
   Hours = std::stoi(str_partition);

   // Get Minutes
   iter++; // Skip the ":" character
   str_partition = "";
   if (!isdigit(*iter))
   {
	   return false;
   }
   while (isdigit(*iter) && iter != str.end())
   {
	   str_partition += *iter;
	   iter++;
   }
   if (str_partition.length() > 2)
   {
	   return false;
   }

   Minutes = std::stoi(str_partition);

   // Get AM/PM
   str_partition = "";
   while (iter != str.end())
   {
	   str_partition += *iter;
	   iter++;
   }
   if (str_partition == "AM")
   {
	   TimeFormat = TimeFormat_t::Format_12_AM;
   }else if (str_partition == "PM")
   {
	   TimeFormat = TimeFormat_t::Format_12_PM;
   }else
   {
	   return false;
   }

	return true;
}
