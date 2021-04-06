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

class GUIStateHabits : public GUIStateBase
{
public:
	GUIStateHabits(GraphicsEngine* gfx_engine, GUIControllerTask* controller, RealTimeClock* rtc) : GUIStateBase(gfx_engine, controller) , m_rtc(rtc) {};
	void UILeft() override {};
	void UIRight() override {};
	void UISelect() override {};
	void UIDraw() override {};
	void OnLoaded() override;
protected:
	RealTimeClock* m_rtc;
private:
	void DrawHabit();
};

#endif /* SRC_GUISTATEHABITS_H_ */
