/*
 * StringUtilities.cpp
 *
 *  Created on: May 19, 2021
 *      Author: keisu
 */

#include "StringUtilities.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Arduino.h>

uint32_t StringUtilities::SplitToUint(uint8_t* buffer, size_t buffer_size, const char delimiter, uint32_t* output_buffer, size_t output_buffer_size)
{
	uint32_t num_splits = 0;
  size_t index = 0;
  size_t PARTITION_MAX_SIZE = 124;// Abitrary value for now
  uint8_t current_partition[PARTITION_MAX_SIZE];
  size_t partition_size = 0;

  memset(current_partition, 0, PARTITION_MAX_SIZE);
	while (index < buffer_size && num_splits < output_buffer_size && partition_size < PARTITION_MAX_SIZE - 1)
	{
		while(index < buffer_size && buffer[index] != delimiter && partition_size < PARTITION_MAX_SIZE - 1)
		{
			current_partition[partition_size++] += buffer[index++];
		}

		if (IsNumeric(current_partition, partition_size))
		{
			output_buffer[num_splits++] = atoi((const char*)current_partition);
			memset(current_partition, 0, PARTITION_MAX_SIZE);
      partition_size = 0;
		}else
		{
			// Skip to end  
			break;
		}

		if (index != buffer_size)
		{
      index++; // Skip delimiter
		}
	}
	return num_splits;
}

bool StringUtilities::IsNumeric(uint8_t* buffer, size_t buffer_size)
{
	size_t index = 0;
	while (index < buffer_size && isdigit((int)(buffer[index])))
	{
		index++;
	}
	return buffer_size > 0 && index == buffer_size;
}
