/*
 * Logger.h
 *
 *  Created on: Mar 31, 2021
 *      Author: keisu
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include "cmsis_os.h"

class Logger
{
public:
   static void Write(osThreadId_t sending_thread, std::string str);
   const static size_t BufferItemSize{256};
};

#endif   
