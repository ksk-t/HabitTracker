/*
 * Logger.h
 *
 *  Created on: Mar 31, 2021
 *      Author: keisu
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <sstream>
#include "cmsis_os.h"

enum class LoggingLevel
{
	None,
	Error,
	Debug
};

class Logger
{
public:
	Logger(LoggingLevel level, std::string module) : m_level(level), m_module(module) {};
	virtual ~Logger();
	std::ostringstream& Get();

	const static size_t BufferItemSize{256};

protected:
   std::ostringstream os;

private:
   // Private to hide these
   Logger(const Logger&);
   Logger& operator =(const Logger&);

   LoggingLevel m_level;
   std::string m_module;
};

#endif   
