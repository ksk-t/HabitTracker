/*
 * Logger.cpp
 *
 *  Created on: Apr 1, 2021
 *      Author: keisu
 */

#include "Logger.h"

extern osMessageQueueId_t g_logger_queueHandle;

void Logger::Write(osThreadId_t sending_thread, std::string str)
{
	std::string final_str = "[" + std::string(osThreadGetName(sending_thread)) + "]: " + str + "\n";
	osMessageQueuePut(g_logger_queueHandle, final_str.c_str(), 0U, 0U);
}

