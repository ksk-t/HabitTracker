/*
 * CommandParser.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef SRC_COMMANDPARSER_H_
#define SRC_COMMANDPARSER_H_

#include "CommandCallableBase.h"
#include "string.h"

enum class Module_t
{
   LEDController
};

struct Command_t
{
	uint8_t* Name;
  uint32_t NameLen;
	uint32_t Code;
	Module_t Module;
};

class CommandParser
{
public:
	CommandParser();
	/*
	 * Reads streams and executes command if a registered command matches the stream input
	 *
	 * @param iostream IOStream to read from and write to
	 *
	 * @return True on success, false otherwise
	 */
	bool Execute(uint8_t* buffer, size_t size); // commant parser sends down io stream to executing function which an write to io stream

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


	size_t MaxCommands();
private:

  const static size_t NUM_MAX_CALLBACKS = 10; 
	CommandCallableBase* m_module_callbacks[NUM_MAX_CALLBACKS];

  const static size_t NUM_MAX_COMMANDS = 32;
	Command_t m_commands[NUM_MAX_COMMANDS];
 
	size_t m_num_commands{0};
};


#endif /* SRC_COMMANDPARSER_H_ */
