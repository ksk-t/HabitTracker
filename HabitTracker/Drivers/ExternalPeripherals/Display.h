/*
 * Display.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 *
 * Description: Interface for displays
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Color.h"
#include "Point.h"

class Display
{
public:
	virtual void Initialize() {};
	virtual void DrawPixel(Point_t point, Color_t color) {};
	virtual void InvertPixel(Point_t point) {};
	virtual uint32_t GetHeight() { return 0; };
	virtual uint32_t GetWidth() { return 0; };
	virtual void Update() {};
};


#endif /* DISPLAY_H_ */
