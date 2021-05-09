/*
 * GraphicsEngine.cpp
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#include "GraphicsEngine.h"
#include "GraphicsUtilities.h"
#include "Logger.h"

const static std::string MODULE_NAME = "GraphicsEngine";

GraphicsEngine::GraphicsEngine(Display* display) :
	m_display(display)
{
	m_font = &ClockFont;
}

void GraphicsEngine::Update()
{
	if (Status_t::OK != m_display->Update())
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "Failed to update display";
	}
}

void GraphicsEngine::Initialize()
{
	if (Status_t::OK != m_display->Initialize())
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "Failed to initialize display";
	}
}

void GraphicsEngine::DrawPixel(const Point_t point, const Color_t color)
{
	m_display->DrawPixel(point, color);
}

size_t GraphicsEngine::DrawChar(const Point_t point, const Color_t color, const char ch)
{
	uint32_t i, b, j;
	Point_t curr_point{point.X, point.Y};

	// Check if character is valid
	if (ch < 32 || ch > 126)
		return 0;

	// Use the font to write
	Character font_char = m_font->GetChar(ch);

	for (i = 0; i < m_font->Height; i++) {

		b = font_char.Data[i];

		for (j = 0; j < font_char.Width; j++) {
			if ((b << j) & 0x8000) {
				curr_point.X = point.X + j;
				m_display->DrawPixel(curr_point, color);
			}
		}
		curr_point.Y++;
	}

	return font_char.Width;
}

void GraphicsEngine::DrawString(Color_t color, std::string str)
{
   Point_t curr_point{0, 0};
   const uint32_t characater_space = 1;

   // Calculate width of string in pixels
   size_t width = 0;
	for (std::string::const_iterator iter = str.begin(); iter != str.end(); iter++)
	{
		Character font_char = m_font->GetChar(*iter);
		width += font_char.Width + characater_space;
	}

	curr_point.X = (m_display->GetWidth() - width) / 2;

	for (std::string::const_iterator iter = str.begin(); iter != str.end(); iter++)
	{
		curr_point.X += this->DrawChar(curr_point, color, *iter) + characater_space;
	}
}

void GraphicsEngine::DrawBox(Point_t point, uint32_t width, uint32_t height, const Color_t outline_color, const Color_t fill_color)
{
	Point_t current_point{point.X, point.Y};

	for (uint32_t x = 0; x < width; x++)
	{
		for (uint32_t y = 0; y < height; y++)
		{
			current_point.X = point.X + x;
			current_point.Y = point.Y + y;
			if (current_point.X < m_display->GetWidth() && current_point.Y < m_display->GetHeight())
			{
				if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				{
					m_display->DrawPixel(current_point, outline_color);
				}else
				{
					m_display->DrawPixel(current_point, fill_color);
				}
			}
		}
	}
}

void GraphicsEngine::Fill(const Color_t color)
{
	Point_t current_point{};
	for (uint32_t x = 0; x < m_display->GetWidth(); x++)
	{
		for (uint32_t y = 0; y < m_display->GetHeight(); y++)
		{
			current_point.X = x;
			current_point.Y = y;
			m_display->DrawPixel(current_point, color);
		}
	}
}

void GraphicsEngine::SetFont(Font* font)
{
	m_font = font;
}

uint32_t GraphicsEngine::GetDisplayHeight()
{
	return m_display->GetHeight();
}

uint32_t GraphicsEngine::GetDisplayWidth()
{
	return m_display->GetWidth();
}

void GraphicsEngine::DrawLine(Point_t point1, Point_t point2, const Color_t color)
{
	  int32_t deltaX = abs(point2.X - point1.X);
	  int32_t deltaY = abs(point2.Y - point1.Y);
	  int32_t signX = ((point1.X < point2.X) ? 1 : -1);
	  int32_t signY = ((point1.Y < point2.Y) ? 1 : -1);
	  int32_t error = deltaX - deltaY;
	  int32_t error2;

	m_display->DrawPixel(point2, color);

	while ((point1.X != point2.X) || (point1.Y != point2.Y))
	{
		m_display->DrawPixel(point1, color);
		error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			point1.X += signX;
		} else {
			/*nothing to do*/
		}

		if (error2 < deltaX) {
			error += deltaX;
			point1.Y += signY;
		} else {
			/*nothing to do*/
		}
	}
}

