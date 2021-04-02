/*
 * GraphicsEngine.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_GRAPHICSENGINE_H_
#define EXTERNALPERIPHERALS_GRAPHICSENGINE_H_

#include "Display.h"
#include "BasicFonts.h"
#include <string>

class GraphicsEngine
{
public:
	GraphicsEngine(Display* display);
	void Initialize();
	void Fill();
	void Update();
	void InvertRegion();
	void DrawChar(const Point_t point, const Color_t, const char ch);
	void SetFont(BasicFont* font);
	void DrawString(Point_t point, Color_t color, std::string string);
	void DrawStringWrap(Color_t color, std::string string);
	void DrawBox(const Point_t point, const uint32_t width, const uint32_t height, const Color_t outline_color, const Color_t fill_color);
	void Fill(const Color_t color);
	uint32_t GetDisplayHeight();
private:
	Display* m_display;
	BasicFont* m_font;
};



#endif /* EXTERNALPERIPHERALS_GRAPHICSENGINE_H_ */
