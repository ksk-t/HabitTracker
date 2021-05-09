/*
 * CommandParser.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#include "CommandParser.h"
#include <cstring>
#include <algorithm>

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
	uint8_t read_buffer[buffer_size] = {0};
	size_t byte_read = iostream->Read(read_buffer, buffer_size);
	std::string cmd_str = "";
	size_t cmd_index = 0;

	// Extract command from buffer
	while (cmd_index < byte_read && read_buffer[cmd_index] != static_cast<uint8_t>(' ') && read_buffer[cmd_index] != 0 && read_buffer[cmd_index] != '\r')
	{
		cmd_str += read_buffer[cmd_index++];
	}

	if (cmd_str == "help")
	{
		PrintHelp(iostream);
		return true;
	}else
	{
		// Find start of command values
		while (cmd_index < byte_read && (read_buffer[cmd_index] == static_cast<uint8_t>(' ') || read_buffer[cmd_index] == static_cast<uint8_t>('\r')))
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
				if (cmd_status_t::Ok == m_module_callbacks[module_index]->CommandCallback(read_buffer + cmd_index, byte_read - cmd_index, cmd.Code, iostream))
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
}

void CommandParser::PrintHelp(IOStreamBase* iostream)
{
	const size_t write_buffer_size = 128;
	uint8_t write_buffer[write_buffer_size] = {0};
	size_t len_longest_cmd_name = 0;
	for (size_t i = 0; i < m_num_commands;i++)
	{
		Command_t cmd = m_commands[i];
		len_longest_cmd_name = std::max(len_longest_cmd_name, cmd.Name.length());
	}

	for (size_t i = 0; i < m_num_commands;i++)
	{
		Command_t cmd = m_commands[i];
		size_t j = 0;
		for (; j < cmd.Name.size() && j < write_buffer_size - 5; j++)
		{
			write_buffer[j] = cmd.Name[j];
		}
		for (; j < len_longest_cmd_name && j < write_buffer_size - 5; j++)
		{
			write_buffer[j] = ' ';
		}

		write_buffer[j++] = ' ';
		write_buffer[j++] = '-';
		write_buffer[j++] = ' ';

		for (size_t k = 0; k < cmd.Help.size() && j < write_buffer_size - 2; j++)
		{
			write_buffer[j] = cmd.Help[k++];
		}

		write_buffer[j++] = '\r';
		write_buffer[j++] = '\n';

		iostream->Write(write_buffer, j);
		std::fill(write_buffer, write_buffer + write_buffer_size, 0);
	}
}

size_t CommandParser::MaxCommands()
{
	return m_commands.size();
}
