/*
 * CommandParser.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef SRC_COMMANDPARSER_H_
#define SRC_COMMANDPARSER_H_

#include "IOStreamBase.h"
#include "CommandCallableBase.h"
#include <functional>
#include <string>

enum class Module_t
{
   HabitManager 
};

struct Command_t
{
	std::string Name;
	std::string Help;
	uint32_t Code;
	Module_t Module;
};

class CommandParser
{
public:
	/*
	 * Reads streams and executes command if a registered command matches the stream input
	 *
	 * @param iostream IOStream to read from and write to
	 *
	 * @return True on success, false otherwise
	 */
	bool Execute(IOStreamBase iostream); // commant parser sends down io stream to executing function which an write to io stream

	/*
	 * Registers a module
	 *
	 * @param module Module to register
	 * @param callback Callback associated with module
	 *
	 * @return true on success, false otherwise
	 */
	bool RegisterModule(Module_t module, CommandCallableBase* callable);

	/*
	 * Registers a command. Module needs to be registered before registering command assocated with module.
	 *
	 * @param command Command to register
	 *
	 * @return true on success, false otherwise
	 */
	bool RegisterCommand(Command_t command);

private:
	static const size_t MAX_NUM_MODULES = 5;
};


#endif /* SRC_COMMANDPARSER_H_ */
