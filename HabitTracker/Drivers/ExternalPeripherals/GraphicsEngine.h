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
#include "Font.h"
#include <string>

class GraphicsEngine
{
public:
	GraphicsEngine(Display* display);
	void Initialize();
	void Fill();
	void Update();
	void InvertRegion();
	void DrawPixel(const Point_t point, const Color_t color);
	size_t DrawChar(const Point_t point, const Color_t, const char ch);
	void SetFont(Font* font);
	void DrawString(Color_t color, std::string str);
	void DrawBox(const Point_t point, const uint32_t width, const uint32_t height, const Color_t outline_color, const Color_t fill_color);
	void DrawLine(const Point_t point1, const Point_t point2, const Color_t color);
	void Fill(const Color_t color);
	uint32_t GetDisplayHeight();
	uint32_t GetDisplayWidth();
private:
	Display* m_display;
	Font* m_font;
};



#endif /* EXTERNALPERIPHERALS_GRAPHICSENGINE_H_ */
