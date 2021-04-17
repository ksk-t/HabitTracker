///*
// * CommandControllerTest.cpp
// *
// *  Created on: Apr 17, 2021
// *      Author: keisu
// */
//
//#include "CommandParser.h"
//#include "IOStreamBase.h"
//
//// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
//#include "CppUTest/TestHarness.h"
//#include "CppUTestExt/MockSupport.h"
//
//class MockCommandCallable : public CommandCallableBase
//{
//public:
//	cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream) override
//	{
//		mock().actualCall("test_callback").withParameter("code", code);
//		return cmd_status_t::Ok;
//	}
//};
//
//class MockIOSteam : public IOStreamBase
//{
//public:
//	size_t Read(uint8_t* buffer, size_t sizes) override
//	{
//		uint8_t test_buffer[] = "testcmd testvalue";
//		return 0;
//	}
//
//	size_t Write(uint8_t* buffer, size_t sizes) override
//	{
//		return 0;
//	}
//};
//
//TEST_GROUP(CommandParserTests)
//{
//	CommandParser *parser;
//	MockCommandCallable* mockcallable;
//	void setup()
//	{
//		parser = new CommandParser();
//		mockcallable = new MockCommandCallable();
//	}
//
//	void teardown()
//	{
//		delete parser;
//		delete mockcallable;
//	}
//};
//
//TEST(CommandParserTests, register_commands)
//{
//	Command_t command;
//	command.Code = 1;
//	command.Help = "Help string";
//	command.Module = Module_t::HabitManager;
//	command.Name = "testcmd";
//	CHECK_FALSE(parser->RegisterCommand(command));
//	CHECK(parser->RegisterModule(Module_t::HabitManager, mockcallable));
//	parser->Execute();
//	mock().expectOneCall("test_callback").withParameter("code", command.Code);
//}
