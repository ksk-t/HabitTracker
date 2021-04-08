/*
 * StatusLED.cpp
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#include "StatusLED.h"
#include "cmsis_os.h"

extern osEventFlagsId_t error_eventHandle;

void StatusLED::SetErrorEvent()
{
	osEventFlagsSet(error_eventHandle, 1U);
}

void StatusLED::ClearErrorEvent()
{
	osEventFlagsClear(error_eventHandle, 1U);
}



