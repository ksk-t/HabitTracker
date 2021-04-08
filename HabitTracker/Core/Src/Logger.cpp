/*
 * Logger.cpp
 *
 *  Created on: Apr 1, 2021
 *      Author: keisu
 */

#include "Logger.h"
#include "StatusLED.h"
#include "cmsis_os.h"

extern osMessageQueueId_t g_logger_queueHandle;

#define LOGGING_DEBUG_ENABLE
#define LOGGING_ERROR_ENABLE
#define LOGGING_LED_ALERT_ENABLE

std::ostringstream& Logger::Get()
{
	os << "[" << std::string(osThreadGetName(osThreadGetId())) << "]["
			<< m_module << "]: ";
	return os;
}

Logger::~Logger()
{
	switch (m_level)
	{
	case LoggingLevel::Debug:
#ifndef LOGGING_DEBUG_ENABLE
		return;
#endif
		break;
	case LoggingLevel::Error:
#ifdef LOGGING_LED_ALERT_ENABLE
		StatusLED::SetErrorEvent();
#endif
#ifndef LOGGING_ERROR_ENABLE
		return;
#endif
		break;
	}

	std::string message = os.str() + "\n";
	osMessageQueuePut(g_logger_queueHandle, message.c_str(), 0U, 0U);
}
