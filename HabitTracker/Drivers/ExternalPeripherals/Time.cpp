/*
 * Time.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: keisu
 */


#include "Time.h"

std::string Time_t::ToString(bool toggle_colon) {
	std::string ret_str = "";

	if (Hours < 10) {
		ret_str += "0";
	}
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

