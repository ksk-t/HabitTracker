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
	Point_t cursor{0, 0};

	// Draw clock on top row
	Color_t color{1, 0, 0};
	size_t first_char_offset = 2;

	m_gfx_engine->Fill(BasicColors::Black);
	m_gfx_engine->DrawString(cursor, color,ClockFont ,m_rtc->GetTime().ToString(true), first_char_offset);

	m_gfx_engine->Update();
}
