/*
 * GUIStateHabits.cpp
 *
 *  Created on: Apr 5, 2021
 *      Author: keisu
 */


#include "GUIStateHabits.h"

void GUIStateHabits::OnLoaded()
{
	DrawHabit();
}

void GUIStateHabits::DrawHabit(/*habit object*/)
{
	BasicFont* time_font = &Font_7x10;
	Point_t cursor{0, m_gfx_engine->GetDisplayHeight() - time_font->FontHeight - 1}; // Display time on top row

	// Draw clock on top row
	m_gfx_engine->SetFont(&Font_7x10);
	m_gfx_engine->Fill(BasicColors::Black());
	m_gfx_engine->DrawString(cursor, BasicColors::White(), m_rtc->GetTime().ToString(true));

	Point_t end_of_line{m_gfx_engine->GetDisplayWidth() - 1, cursor.Y};
	m_gfx_engine->DrawLine(cursor, end_of_line, BasicColors::White());
	m_gfx_engine->Update();
}
