/*
 * GraphicsUtilitiesTests.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keisu
 */

#include "GraphicsUtilities.h"

// Includes CppUtest headers last since they can potentially override functions/keywords used before ('new' for example)
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(GraphicsUtilitiesTests)
{
	// Virtual LCD display and font configuration
	const uint32_t screen_width = 128;
	const uint32_t screen_height = 64;
	const uint32_t font_height = 10;
	const uint32_t font_width = 7;

};

TEST(GraphicsUtilitiesTests, split_string)
{
	std::string test = "      this is a sample.       ";
	const size_t max_words = 100;
	std::string words[max_words];

	LONGS_EQUAL(4, GraphicsUtilities::SplitString(test, words, max_words, font_width, screen_width));
	STRCMP_EQUAL("this", words[0].c_str());
	STRCMP_EQUAL("is", words[1].c_str());
	STRCMP_EQUAL("a", words[2].c_str());
	STRCMP_EQUAL("sample.", words[3].c_str());
}

TEST(GraphicsUtilitiesTests, split_string_overflow_buffer)
{

	std::string test = "this is a sample.";
	const size_t max_words = 3;
	std::string words[max_words];


	LONGS_EQUAL(4, GraphicsUtilities::SplitString(test, words, max_words, font_width, screen_width));
}

TEST(GraphicsUtilitiesTests, split_string_long_word)
{
	std::string test = "thisisareallylongword short";
	const size_t max_words = 3;
	std::string words[max_words];

	LONGS_EQUAL(3, GraphicsUtilities::SplitString(test, words, max_words, font_width, screen_width));
	STRCMP_EQUAL("thisisareallylongw", words[0].c_str());
	STRCMP_EQUAL("ord", words[1].c_str());
	STRCMP_EQUAL("short", words[2].c_str());
}

TEST(GraphicsUtilitiesTests, wrap_text_single_line)
{
	std::string test = "this is a sample";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width);
	STRCMP_EQUAL("this is a sample", lines[0].c_str());
}

TEST(GraphicsUtilitiesTests, wrap_text_basic)
{
	std::string test = "this is a sampleee text string that will get wrapped.";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	LONGS_EQUAL(3, GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width));
	STRCMP_EQUAL("this is a sampleee", lines[0].c_str());
	STRCMP_EQUAL("text string that", lines[1].c_str());
	STRCMP_EQUAL("will get wrapped.", lines[2].c_str());
}

TEST(GraphicsUtilitiesTests, wrap_text_word_longer_than_line)
{
	std::string test = "this is a sampletextstringstring that will get wrapped.";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	LONGS_EQUAL(4,  GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width));
	STRCMP_EQUAL("this is a", lines[0].c_str());
	STRCMP_EQUAL("sampletextstringst", lines[1].c_str());
	STRCMP_EQUAL("ring that will get", lines[2].c_str());
	STRCMP_EQUAL("wrapped.", lines[3].c_str());
}

TEST(GraphicsUtilitiesTests, wrap_text_word_wraps_two_lines)
{

	std::string test = "this is a samplestringsamplestringsamplestring";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	LONGS_EQUAL(3, GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width));
	STRCMP_EQUAL("this is a", lines[0].c_str());
	STRCMP_EQUAL("samplestringsample", lines[1].c_str());
	STRCMP_EQUAL("stringsamplestring", lines[2].c_str());
}

TEST(GraphicsUtilitiesTests, split_text_new_line)
{
	std::string test = "this is\n a\n sample";
	const size_t max_words = 6;
	size_t current_word = 0;
	std::string words[max_words];

	LONGS_EQUAL(6, GraphicsUtilities::SplitString(test, words, max_words, font_width, screen_width));
	STRCMP_EQUAL("this", words[current_word++].c_str());
	STRCMP_EQUAL("is", words[current_word++].c_str());
	STRCMP_EQUAL("\n", words[current_word++].c_str());
	STRCMP_EQUAL("a", words[current_word++].c_str());
	STRCMP_EQUAL("\n", words[current_word++].c_str());
	STRCMP_EQUAL("sample", words[current_word++].c_str());
}

TEST(GraphicsUtilitiesTests, wrap_text_new_line)
{
	std::string test = "this is a\n sample \nstring";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	LONGS_EQUAL(3, GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width));
	STRCMP_EQUAL("this is a", lines[0].c_str());
	STRCMP_EQUAL("sample", lines[1].c_str());
	STRCMP_EQUAL("string", lines[2].c_str());
}


TEST(GraphicsUtilitiesTests, wrap_text_two_new_lines_backtoback)
{

	std::string test = "this is a\n\nsample string";
	const uint32_t num_lines = screen_height / font_height;
	std::string lines[num_lines];

	LONGS_EQUAL(3, GraphicsUtilities::WrapText(test, lines, num_lines, font_width, screen_width));
	STRCMP_EQUAL("this is a", lines[0].c_str());
	STRCMP_EQUAL("", lines[1].c_str());
	STRCMP_EQUAL("sample string", lines[2].c_str());
}


