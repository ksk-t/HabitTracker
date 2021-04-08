/*
 * LEDStatusTask.cpp
 *
 *  Created on: Apr 6, 2021
 *      Author: keisu
 */

#include "LEDStatusTask.h"
#include "cmsis_os.h"
#include "StatusLED.h"

static const uint32_t REFRESH_INTERVAL = 100;

void LEDStatusTask::Run()
{
   for(;;)
   {
      LEDState_t state = StatusLED::GetState();
      switch(state)
      {
         case LEDState_t::Ok:
            break;
         case LEDState_t::Error:
            break;
      }     

      osDelay(REFRESH_INTERVAL);
   }
}


