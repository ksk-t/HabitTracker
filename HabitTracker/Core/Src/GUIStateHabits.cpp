/*
 * GUIStateHabits.cpp
 *
 *  Created on: Apr 5, 2021
 *      Author: keisu
 */


#include "GUIStateHabits.h"
#include "HabitManager.h"

GUIStateHabits::GUIStateHabits(GraphicsEngine* gfx_engine, GUIControllerTask* controller, RealTimeClock* rtc, HabitManager *habit_manager) :
	GUIStateBase(gfx_engine, controller),
	m_rtc(rtc),
	m_habit_manager(habit_manager)
{
	Habit_t habit;
	habit.Name = "test habit";
	habit.IsComplete = true;
	habit.Streak = 123;

	m_habit_manager->AddHabit(habit);

	habit.Name = "habit 2";
	habit.IsComplete = false;
	habit.Streak = 1;

	m_habit_manager->AddHabit(habit);
}

void GUIStateHabits::UILeft()
{
	if (m_habit_index > 0)
	{
		Habit_t habit;
		if (m_habit_manager->GetHabit(--m_habit_index, habit))
		{
			DrawHabit(habit);
		}else
		{
			DrawStringWithTime("Error getting habit");
		}
	}
}

void GUIStateHabits::UIRight()
{
	if (m_habit_index < m_habit_manager->Count() - 1)
	{
		Habit_t habit;
		if (m_habit_manager->GetHabit(++m_habit_index, habit))
		{
			DrawHabit(habit);
		}else
		{
			DrawStringWithTime("Error getting habit");
		}
	}
}

void GUIStateHabits::OnLoaded()
{
	Habit_t habit;
	m_habit_index = 0;
	if (m_habit_manager->GetHabit(m_habit_index, habit))
	{
		DrawHabit(habit);
	}else
	{
		DrawStringWithTime("No Habits");
	}
}

void GUIStateHabits::DrawStringWithTime(std::string str)
{
	BasicFont* font = &Font_7x10;
	Point_t cursor{0, m_gfx_engine->GetDisplayHeight() - font->FontHeight - 1}; // Display time on top row

	// Draw clock on top row
	m_gfx_engine->SetFont(&Font_7x10);
	m_gfx_engine->Fill(BasicColors::Black());
	m_gfx_engine->DrawString(cursor, BasicColors::White(), m_rtc->GetTime().ToString(true));
	Point_t end_of_line{m_gfx_engine->GetDisplayWidth() - 1, cursor.Y};
	m_gfx_engine->DrawLine(cursor, end_of_line, BasicColors::White());
	cursor.Y -= font->FontHeight + 1;

	// Draw string
	m_gfx_engine->DrawStringWrap(cursor, BasicColors::White(), str);
	m_gfx_engine->Update();
}

void GUIStateHabits::DrawHabit(Habit_t habit)
{
	std::string habit_string = habit.Name;
	habit_string += "\nStatus: ";
	habit_string += (habit.IsComplete) ? "Complete" : "Incomplete";
	habit_string += "\nStreak: " + std::to_string(habit.Streak);

	DrawStringWithTime(habit_string);
}
