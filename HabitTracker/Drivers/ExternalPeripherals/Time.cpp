/*
 * Time.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: keisu
 */


#include "Time.h"
#include "StringUtilities.h"

std::string Time_t::ToString(bool toggle_colon) {
	std::string ret_str = "";

	if (Hours == 11)
	{
		ret_str = "1   1"; // #HACK: Special spacing for 11 to look better when displayed
	}else
	{
		ret_str += std::to_string(Hours);
	}

	if (toggle_colon && Seconds % 2 == 1) {
		ret_str += "  ";
	} else {
		ret_str += ":";
	}
	if (Minutes < 10)
	{
		ret_str += "0";
		ret_str += std::to_string(Minutes);
	}else if (Minutes == 11)
	{
		ret_str += "1   1"; // #HACK: Special spacing for 11 to look better when displayed
	}else
	{
		ret_str += std::to_string(Minutes);
	}

	if (TimeFormat == TimeFormat_t::Format_12_AM) {
		ret_str += "AM";
	} else {
		ret_str += "PM";
	}

	return ret_str;
}

bool Time_t::FromString(std::string str)
{
	size_t buffer_size = 3;
	uint32_t parse_buffer[buffer_size] = {0};
	if (buffer_size != StringUtilities::SplitToUint(str, ':', parse_buffer, buffer_size))
	{
		return false;
	}

	// Set hours and time format
	if (parse_buffer[0] > 23)
	{
		return false;
	}else if (parse_buffer[0] > 12)
	{
		Hours = parse_buffer[0] - 12;
		TimeFormat = TimeFormat_t::Format_12_PM;
	}else if (parse_buffer[0] == 0)
	{
		Hours = 12;
		TimeFormat = TimeFormat_t::Format_12_AM;
	}else
	{
		Hours = parse_buffer[0];
		TimeFormat = TimeFormat_t::Format_12_AM;
	}

	// Set Minutes
	if (parse_buffer[1] > 59)
	{
		return false;
	}else
	{
		Minutes = parse_buffer[1];
	}

	// Set seconds
	if (parse_buffer[2] > 59)
	{
		return false;
	}else
	{
		Seconds = parse_buffer[2];
	}

	return true;
}
