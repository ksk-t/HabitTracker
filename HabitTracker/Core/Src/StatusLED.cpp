/*
 * StatusLED.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: keisu
 */

#include "StatusLED.h"

void StatusLED::SetState(LEDState_t state)
{
   m_state = state;
}

LEDState_t StatusLED::GetState()
{
   LEDState_t ret = m_state;

   return ret;
}

