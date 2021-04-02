/*
 * GUIStateClock.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: keisu
 */


#include "GUIStateClock.h"

void GUIStateClock::OnLoaded()
{
	this->DrawTime();
}

void GUIStateClock::UIDraw()
{
	this->DrawTime();
}

void GUIStateClock::DrawTime()
{
	BasicFont* font = &Font_16x26;
	m_gfx_engine->SetFont(font);
	Point_t point{0, m_gfx_engine->GetDisplayHeight() / 2 - font->FontHeight / 2};

	m_gfx_engine->Fill(BasicColors::White());
	m_gfx_engine->DrawString(point, BasicColors::White(),  "testval");
	m_gfx_engine->Update();
}


