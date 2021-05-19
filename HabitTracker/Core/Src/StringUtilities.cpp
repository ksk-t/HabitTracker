/*
 * StringUtilities.cpp
 *
 *  Created on: May 19, 2021
 *      Author: keisu
 */

#include "StringUtilities.h"

uint32_t StringUtilities::SplitToUint(std::string str, const char delimiter, uint32_t* output_buffer, size_t buffer_size)
{
	uint32_t num_splits = 0;
	std::string current_partition = "";
	std::string::iterator iter = str.begin();

	while (iter != str.end() && num_splits < buffer_size)
	{
		while(iter != str.end() && *iter != delimiter)
		{
			current_partition += *iter;
			iter++;
		}

		if (IsNumeric(current_partition))
		{
			output_buffer[num_splits++] = std::stoi(current_partition);
			current_partition = "";
		}else
		{
			// Skip to end
			iter = str.end();
		}

		if (iter != str.end())
		{
			iter++; // Skip delimiter
		}
	}
	return num_splits;
}

bool StringUtilities::IsNumeric(std::string str)
{
	std::string::const_iterator iter = str.begin();
	while (iter != str.end() && std::isdigit(*iter))
	{
		iter++;
	}

	return !str.empty() && iter == str.end();
}
