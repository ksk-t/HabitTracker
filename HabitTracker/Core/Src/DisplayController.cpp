/*
 * DisplayController.cpp
 *
 *  Created on: May 1, 2021
 *      Author: keisu
 */

#include "DisplayController.h"

DisplayController::DisplayController(GraphicsEngine* gfx_engine, RealTimeClock* rtc, HabitManager* habit_manager)
{
   m_gfx_engine = gfx_engine;
   m_rtc = rtc;
   m_habit_manager = habit_manager;

   m_gfx_engine->Initialize();
   rtc->Initialize();
}

void DisplayController::Draw()
{
   // Draw Clock
  	BasicFont* font = &Font_6x8;
	Point_t cursor{5, 0};

	m_gfx_engine->SetFont(font);
	m_gfx_engine->Fill(BasicColors::Black);

//	// TEMP:Draw bounding box of LED matrix that will be used
//	Point_t top_left{0, m_gfx_engine->GetDisplayHeight() - 19}; // Display time on top row
//	m_gfx_engine->DrawBox(top_left, 34, 18, BasicColors::White, BasicColors::Black);
//
	// Draw clock on top row
	Color_t color{1, 0, 0};
	m_gfx_engine->DrawString(cursor, color,ClockFont ,m_rtc->GetTime().ToString(true));

	m_gfx_engine->Update();
}
