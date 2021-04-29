/*
 * GUIStateClock.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: keisu
 */


#include "GUIStateClock.h"
#include "Logger.h"

static const std::string MODULE_NAME = "GUIStateClock";

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
	if (m_gfx_engine == nullptr)
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "GFX Engine null";
		return;
	}

	BasicFont* font = &Font_16x26;
	m_gfx_engine->SetFont(font);
	Point_t point{0, m_gfx_engine->GetDisplayHeight() / 2 - font->FontHeight / 2};

	m_gfx_engine->Fill(BasicColors::Black);
	m_gfx_engine->DrawString(point, BasicColors::White,  "testval");
	m_gfx_engine->Update();
}


