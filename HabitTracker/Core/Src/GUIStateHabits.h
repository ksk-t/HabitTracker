/*
 * GUIStateHabits.h
 *
 *  Created on: Apr 5, 2021
 *      Author: keisu
 */

#ifndef SRC_GUISTATEHABITS_H_
#define SRC_GUISTATEHABITS_H_

#include "GUIStateBase.h"
#include "RealTimeClock.h"
#include "HabitManager.h"

class GUIStateHabits : public GUIStateBase
{
public:
	GUIStateHabits(GraphicsEngine* gfx_engine, GUIControllerTask* controller, RealTimeClock* rtc, HabitManager *habit_manager);
	void UILeft() override;
	void UIRight() override;
	void UISelect() override;
	void UIDraw() override;
	void OnLoaded() override;
protected:
	RealTimeClock* m_rtc;
	HabitManager* m_habit_manager;
private:
	void DrawHabit(Habit_t);
	void DrawStringWithTime(std::string str);
	size_t m_habit_index{0};
};

#endif /* SRC_GUISTATEHABITS_H_ */
