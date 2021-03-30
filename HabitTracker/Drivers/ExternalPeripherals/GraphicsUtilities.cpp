/*
 * GraphicsUtilities.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keisu
 */

#include "GraphicsUtilities.h"

size_t GraphicsUtilities::SplitString(std::string input, std::string output[], size_t output_size, uint32_t font_width, uint32_t screen_width)
{
	std::string current_word = "";
	size_t current_word_index = 0;

	for (std::string::const_iterator iter = input.begin(); iter != input.end(); iter++)
	{
		if (*iter == '\n')
		{
			// Add current string of characters as a word
			if (current_word.length() > 0)
			{
				if (current_word_index < output_size)
				{
					output[current_word_index++] = current_word;
					current_word = "";
				}

			}

			// Add the newline as its own "word"
			if (current_word_index < output_size)
			{
				output[current_word_index++] = "\n";
			}

		}else if (*iter == ' ')
		{
			// Add current string of characters as a word
			if (current_word.length() > 0)
			{
				if (current_word_index < output_size)
				{
					output[current_word_index++] = current_word;
					current_word = "";
				}

			}else
			{
				// Throw away space character if current word length is empty;
			}

		}else
		{
			// Check if adding character will make word longer than width of screen
			if ((current_word.length() + 1) * font_width < screen_width)
			{// If not add character
				current_word += *iter;
			}else
			{// If yes, cut off word and continue the word onto the next string
				if (current_word_index < output_size)
				{
					output[current_word_index++] = current_word;
					current_word = *iter;
				}
			}
		}
	}

	// Add any remaining characters as a word
	if (current_word.length() > 0)
	{
		if (current_word_index < output_size)
		{
			output[current_word_index++] = current_word;
			current_word = "";
		}

	}
	return current_word_index;
}

size_t GraphicsUtilities::WrapText(std::string input, std::string output[], size_t output_size, uint32_t font_width, uint32_t screen_width)
{

	const size_t max_words = 100;
	std::string words[max_words];
	size_t current_line_index = 0;
	std::string current_line = "";
	uint32_t max_characters_per_line = screen_width / font_width;

	size_t num_words = SplitString(input, words, max_words, font_width, screen_width);
	if ( num_words > max_words)
	{
		return 0;
	}

	for (size_t i = 0; i < num_words; i++)
	{
		size_t line_length = current_line.length() + words[i].length();
		if (words[i] == "\n")
		{// New line
			if (current_line.length() > 0)
			{// End current line as it is and move on to next line
				output[current_line_index++] = current_line;
				current_line = "";
			}else
			{// Create empty line
				output[current_line_index++] = "";
			}
		}
		else if (line_length == max_characters_per_line && current_line.length() == 0)
		{// Current line is empty and next word is equal to the maximum number of characters per line
			output[current_line_index++] = words[i];
		}
		else if ((1 + line_length) > max_characters_per_line) // the + 1 is for the space
		{// space + next word is too long
			output[current_line_index++] = current_line;
			current_line = "";

			// Kind of a hack but decrement i so that the word that would have
			// went out of bounds can be drawn in the next line
			i--;
		}else
		{// Enough room is available for a space + the next word
			if (current_line.length() > 0) // do not add a space if first word in line
			{
				current_line += " ";
			}
			current_line += words[i];
		}
	}

	if (current_line.length() > 0)
	{
		output[current_line_index++] = current_line;
		current_line = "";
	}

	return current_line_index;
}

