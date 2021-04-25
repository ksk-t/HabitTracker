/*
 * CommandParser.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#include "CommandParser.h"
#include <cstring>

CommandParser::CommandParser()
{
	m_module_callbacks.fill(nullptr);
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
	if (m_module_callbacks[static_cast<size_t>(command.Module)] == nullptr || m_num_commands >= m_commands.size())
	{
		return false;
	}

	m_commands[m_num_commands++] = command;
	return true;
}

bool CommandParser::Execute(IOStreamBase* iostream)
{
	const size_t buffer_size = 128;
	uint8_t read_buffer[buffer_size];
	size_t byte_read = iostream->Read(read_buffer, buffer_size);
	std::string cmd_str = "";
	size_t cmd_index = 0;
	uint8_t msg_invalid_cmd[] = "Invalid command";

	// Extract command from buffer
	while (cmd_index < byte_read && read_buffer[cmd_index] != static_cast<uint8_t>(' ') && read_buffer[cmd_index] != 0 && read_buffer[cmd_index] != '\r')
	{
		cmd_str += read_buffer[cmd_index++];
	}

	// Find start of command values
	while (cmd_index < byte_read && read_buffer[cmd_index] == static_cast<uint8_t>(' '))
	{
		cmd_index++;
	}

	// Search command list for given command
	for (size_t i = 0; i < m_num_commands;i++)
	{
		Command_t cmd = m_commands[i];
		if (cmd_str == cmd.Name)
		{
			size_t module_index = static_cast<size_t>(cmd.Module);
			m_module_callbacks[module_index]->CommandCallback(read_buffer + cmd_index, byte_read - cmd_index, cmd.Code, iostream);
			return true;
		}
	}

	iostream->Write(msg_invalid_cmd, sizeof(msg_invalid_cmd) / sizeof(msg_invalid_cmd[0]));
	return false;
}

size_t CommandParser::MaxCommands()
{
	return m_commands.size();
}
