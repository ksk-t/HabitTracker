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
#include "Status.h"

class Display
{
public:
	virtual Status_t Initialize() { return Status_t::OK; };
	virtual Status_t DrawPixel(Point_t point, Color_t color) { return Status_t::OK; };
	virtual uint32_t GetHeight() { return 0; };
	virtual uint32_t GetWidth() { return 0; };
	virtual Status_t Update() { return Status_t::OK; };
};


#endif /* DISPLAY_H_ */
