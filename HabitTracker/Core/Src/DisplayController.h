/*
 * DisplayController.h
 *
 *  Created on: May 1, 2021
 *      Author: keisu
 */

#ifndef SRC_DISPLAYCONTROLLER_H_
#define SRC_DISPLAYCONTROLLER_H_

#include "HabitManager.h"
#include "GraphicsEngine.h"
#include "RealTimeClock.h"

class DisplayController
{
public:
   DisplayController(GraphicsEngine* gEngine, RealTimeClock* rtc, HabitManager* habit_manager);

	/*
	 * Update the display
	 */
	void Draw();
private:
   GraphicsEngine* m_gfx_engine;
   RealTimeClock* m_rtc;
   HabitManager* m_habit_manager;
};


#endif /* SRC_DISPLAYCONTROLLER_H_ */
