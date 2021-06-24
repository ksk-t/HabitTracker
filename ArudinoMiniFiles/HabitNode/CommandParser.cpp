/*
 * CommandParser.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#include "CommandParser.h"
#include <Arduino.h>

CommandParser::CommandParser()
{
  for (size_t i = 0; i < NUM_MAX_CALLBACKS; i++)
  {
      m_module_callbacks[i] = nullptr;
  }
}

bool CommandParser::RegisterModule(Module_t module, CommandCallableBase* callable)
{
	size_t module_index = static_cast<size_t>(module);
	m_module_callbacks[module_index] = callable;
	return true;
}

bool CommandParser::RegisterCommand(Command_t command)
{
	// Verify that callback is registered
	if (m_module_callbacks[static_cast<size_t>(command.Module)] == nullptr || m_num_commands >= NUM_MAX_COMMANDS)
	{
		return false;
	}

	m_commands[m_num_commands++] = command;
	return true;
}

bool CommandParser::Execute(uint8_t* read_buffer, size_t byte_read)
{
	const size_t buffer_size = 128;
  const size_t cmd_buffer_max_size = 64;
  size_t cmd_buffer_size = 0;
  uint8_t cmd_buffer[cmd_buffer_max_size] = {0};  

	size_t cmd_index = 0;

	// Extract command from buffer
	while (cmd_index < byte_read && read_buffer[cmd_index] != static_cast<uint8_t>(' ') && read_buffer[cmd_index] != 0 && read_buffer[cmd_index] != '\r')
	{
		cmd_buffer[cmd_buffer_size++] = read_buffer[cmd_index++];
	}

		// Find start of command values
		while (cmd_index < byte_read && (read_buffer[cmd_index] == static_cast<uint8_t>(' ') || read_buffer[cmd_index] == static_cast<uint8_t>('\r')))
		{
			cmd_index++;
		}

		// Extract command from buffer
		size_t parameters_len = 0;
		size_t parameter_index = cmd_index;
		while (cmd_index < byte_read && read_buffer[parameter_index] != 0 && read_buffer[parameter_index] != '\r')
		{
			parameters_len++;
			parameter_index++;
		}

		// Search command list for given command
		for (size_t i = 0; i < m_num_commands;i++)
		{
			Command_t cmd = m_commands[i];
  
			if (strcmp((const char*)cmd_buffer, (const char*)cmd.Name) == 0)
			{
				size_t module_index = static_cast<size_t>(cmd.Module);
				if (cmd_status_t::Ok == m_module_callbacks[module_index]->CommandCallback(read_buffer + cmd_index, parameters_len, cmd.Code))
				{
					return true;
				}else
				{
					return false;
				}
			}
		}

		return false;
}

size_t CommandParser::MaxCommands()
{
	return NUM_MAX_COMMANDS;
}
