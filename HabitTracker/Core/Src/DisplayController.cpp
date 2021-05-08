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

   for (size_t i = 0; i < 8; i++)
   {
	   for (size_t j = 0; j < 32; j++)
	   {
		   m_habit_manager->ToggleHabit(i, j);
	   }
   }
}

void DisplayController::Draw()
{
	Point_t cursor{0, 0};

	// Draw clock on top row
	Color_t color{1, 0, 0};
	size_t first_char_offset = 0;

	m_gfx_engine->Fill(BasicColors::Black);

	Time_t current_time = m_rtc->GetTime();
	if (current_time.Hours >= 10 && current_time.Hours <= 19)
	{
		first_char_offset = 2;
		cursor.X = 0;
	}else
	{
		first_char_offset = 0;
		cursor.X = 2;
	}
	m_gfx_engine->DrawString(cursor, color ,m_rtc->GetTime().ToString(true), first_char_offset);

	// Draw habits
	cursor.X = 0;
	cursor.Y = 8;
	color.B = 7;
	color.R = 0;
	color.G = 0;

	for (size_t i = 0; i < m_habit_manager->Count(); i++)
	{
		for (size_t j = 0; j < m_habit_manager->RecordLength(); j++)
		{
			if (m_habit_manager->GetHabitStatus(i, j))
			{
				cursor.X = j;
				m_gfx_engine->DrawPixel(cursor, color);
			}
		}
		color.B--;
		color.R++;
		cursor.Y++;
	}

	m_gfx_engine->Update();
}
