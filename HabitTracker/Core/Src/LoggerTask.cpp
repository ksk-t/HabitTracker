/*
 * LoggerTask.cpp
 *
 *  Created on: Apr 1, 2021
 *      Author: keisu
 */

#include "LoggerTask.h"
#include "stm32f2xx_hal.h"
#include "Logger.h"
#include "cmsis_os.h"
#include <cstring>

extern osMessageQueueId_t g_logger_queueHandle;

void LoggerTask::Run()
{
   osStatus_t status;
   uint8_t buffer[Logger::BufferItemSize] = {0};
   for (;;)
   {
      status = osMessageQueueGet(g_logger_queueHandle, buffer, NULL, 0U);
      if (status == osOK)
      {
         size_t i = 0;
         char c = buffer[i];
         while (c)
         {
            ITM_SendChar(c);
            c = buffer[++i];
         }

         memset(buffer, 0, Logger::BufferItemSize);
      }
   }
}

