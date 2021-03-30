/*
 * GraphicsUtilities.h
 *
 *  Created on: Mar 29, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_GRAPHICSUTILITIES_H_
#define EXTERNALPERIPHERALS_GRAPHICSUTILITIES_H_

#include <cstddef>
#include <string>

class GraphicsUtilities
{
public:
   static size_t SplitString(std::string input, std::string output[], size_t output_size, uint32_t font_width, uint32_t screen_width);
   static size_t WrapText(std::string input, std::string output[], size_t output_size, uint32_t font_width, uint32_t screen_width);
};

#endif /* EXTERNALPERIPHERALS_GRAPHICSUTILITIES_H_ */
