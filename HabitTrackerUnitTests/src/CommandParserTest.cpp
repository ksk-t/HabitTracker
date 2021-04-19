/*
 * CommandControllerTest.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#include "CommandParser.h"
#include "IOStreamMock.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

class MockCommandCallable : public CommandCallableBase
{
public:
	cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream) override
	{
		mock().actualCall("test_callback").withParameter("size", size).withParameter("code", code);
		return cmd_status_t::Ok;
	}
};

TEST_GROUP(CommandParserTests)
{
	CommandParser *parser;
	MockCommandCallable* mockcallable;
	IOStreamMock* iostream;
	void setup()
	{
		parser = new CommandParser();
		mockcallable = new MockCommandCallable();
		iostream = new IOStreamMock();
	}

	void teardown()
	{
		delete parser;
		delete mockcallable;
		delete iostream;

		mock().clear();
	}

	size_t leading_whitespace(std::string str)
	{
		size_t count = 0;
		std::string::const_iterator iter = str.begin();
		while (*iter == ' ' && iter != str.end())
		{
			iter++;
			count++;
		}

		return count;
	}
};

TEST(CommandParserTests, register_commands)
{
	Command_t command;
	command.Code = 1;
	command.Help = "Help string";
	command.Module = Module_t::HabitManager;
	command.Name = "testcmd";

	// Try to register a command with a module was not registered
	CHECK_FALSE(parser->RegisterCommand(command));
	CHECK(parser->RegisterModule(Module_t::HabitManager, mockcallable));

	// Should register now that the module has been registered
	CHECK(parser->RegisterCommand(command));
}

TEST(CommandParserTests, execute_basic_command)
{
	// Register Module
	CHECK(parser->RegisterModule(Module_t::HabitManager, mockcallable));

	// Register command and execute it with the string
	Command_t command;
	command.Code = 1;
	command.Help = "Help string";
	command.Module = Module_t::HabitManager;
	command.Name = "testcmd";
	CHECK(parser->RegisterCommand(command));
	mock().expectOneCall("test_callback").withParameter("size", 0).withParameter("code", command.Code);
	iostream->WriteReadBuffer((uint8_t*)command.Name.c_str(), command.Name.size());
	CHECK(parser->Execute(iostream));

	// Register and execute second command
	command.Code = 2;
	command.Help = "Help string2";
	command.Module = Module_t::HabitManager;
	command.Name = "testcmd2";
	CHECK(parser->RegisterCommand(command));
	mock().expectOneCall("test_callback").withParameter("size", 0).withParameter("code", command.Code);
	iostream->WriteReadBuffer((uint8_t*)command.Name.c_str(), command.Name.size());
	CHECK(parser->Execute(iostream));

	// Try to execute a command that wasn't registered
	command.Name = "testcmd3";
	iostream->WriteReadBuffer((uint8_t*)command.Name.c_str(), command.Name.size());
	CHECK_FALSE(parser->Execute(iostream));

	mock().checkExpectations();
}

TEST(CommandParserTests, exectute_with_extra_data_in_stream)
{
	// Register Module
	CHECK(parser->RegisterModule(Module_t::HabitManager, mockcallable));

	// Register command and execute it with the string
	Command_t command;
	command.Code = 1;
	command.Help = "Help string";
	command.Module = Module_t::HabitManager;
	command.Name = "testcmd";
	CHECK(parser->RegisterCommand(command));

	// Append extra data to the command
	std::string extra_string = " randomdata";
	std::string iostream_str = command.Name + extra_string;
	iostream->WriteReadBuffer((uint8_t*)iostream_str.c_str(), iostream_str.size());

	mock().expectOneCall("test_callback").withParameter("size", iostream_str.size() - command.Name.size() - leading_whitespace(extra_string)).withParameter("code", command.Code);
	CHECK(parser->Execute(iostream));

	mock().checkExpectations();
}

TEST(CommandParserTests, register_too_many_commands)
{
	Command_t command;
	command.Code = 1;
	command.Help = "Help string";
	command.Module = Module_t::HabitManager;
	command.Name = "testcmd";

	CHECK(parser->RegisterModule(Module_t::HabitManager, mockcallable));

	for (size_t i = 0; i < parser->MaxCommands(); i++)
	{
		CHECK(parser->RegisterCommand(command));
	}

	CHECK_FALSE(parser->RegisterCommand(command));
}
