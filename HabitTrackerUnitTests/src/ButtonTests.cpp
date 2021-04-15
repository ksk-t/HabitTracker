/*
 * ButtonTests.cpp
 *
 *  Created on: Apr 14, 2021
 *      Author: keisu
 */


#include "Button.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(ButtonTests)
{
	Button *button;
	const uint32_t consecutive_resets_required = 12;
	void setup()
	{
		button = new Button();
	}

	void teardown()
	{
		delete button;
	}
};

TEST(ButtonTests, button_pressed)
{
	for (uint32_t i = 0; i < consecutive_resets_required - 1; i++)
	{
		CHECK_FALSE(button->IsPressed(false));
	}
	CHECK(button->IsPressed(false));
}

TEST(ButtonTests, button_pressed_twice)
{
	for (uint32_t i = 0; i < consecutive_resets_required - 1; i++)
	{
		CHECK_FALSE(button->IsPressed(false));
	}
	CHECK(button->IsPressed(false));

	CHECK_FALSE(button->IsPressed(true));

	for (uint32_t i = 0; i < consecutive_resets_required - 1; i++)
	{
		CHECK_FALSE(button->IsPressed(false));
	}
	CHECK(button->IsPressed(false));
}

