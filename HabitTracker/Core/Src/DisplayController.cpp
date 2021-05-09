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

void DisplayController::SetBrightness(uint8_t brightness)
{
	if (brightness > MAX_BRIGHTNESS)
	{
		m_brightness = MAX_BRIGHTNESS;
	}else if (brightness == 0)
	{
		m_brightness = 1;
	}else
	{
		m_brightness = brightness;
	}
}

void DisplayController::Draw()
{
	Point_t cursor{0, 0};

	// Draw clock on top row
	Color_t color{uint8_t(1 + ((m_brightness - 1) * 20)), 0, 0};
	size_t first_char_offset = 0;

	m_gfx_engine->Fill(BasicColors::Black);

	Time_t current_time = m_rtc->GetTime();
	if (current_time != m_last_time)
	{
		m_last_time = current_time;
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
		color.B = (m_habit_manager->Count() - 1) * m_brightness;
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
					color.R += m_brightness;
				}
			}
			color.B -= m_brightness;
			color.G += m_brightness;
			color.R = 0;
			cursor.Y++;
		}

		m_gfx_engine->Update();
	}
}

cmd_status_t DisplayController::CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream)
{
	switch(code)
	{
	case DISPLAY_CMD_SET_BRIGHTNESS:
	{
		if (size > 0)
		{
			std::string brightness((char*)buffer, size - 1); // - 1 to remove the \r

			if (isdigit(brightness[0]))
			{   // The first character at least needs to be a digit
				SetBrightness(std::stoi(brightness));
				uint8_t msg[] = "Brightness set";
				iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
				return cmd_status_t::Ok;
			}else
			{
				uint8_t msg[] = "ERROR: Invalid brightness value";
				iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
				return cmd_status_t::InvalidParamter;
			}

		}else
		{
			uint8_t msg[] = "ERROR: Empty parameter list";
			iostream->Write(msg, sizeof(msg) / sizeof(msg[0]));
			return cmd_status_t::InvalidParamter;
		}

		break;
	}
	default:
		return cmd_status_t::InvalidCode;
	}
}
