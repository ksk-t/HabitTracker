/*
 * StatusLED.cpp
 *
 *  Created on: Apr 8, 2021
 *      Author: keisu
 */

#include "StatusLED.h"
#include "main.h"


void StatusLED::SetErrorEvent()
{
   HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}

void StatusLED::ClearErrorEvent()
{
   HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}
