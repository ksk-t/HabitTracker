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
#include "CommandCallableBase.h"

#define DISPLAY_CMD_SET_BRIGHTNESS 0

class DisplayController : public CommandCallableBase
{
public:
   DisplayController(GraphicsEngine* gEngine, RealTimeClock* rtc, HabitManager* habit_manager);

	/*
	 * Update the display
	 */
	void Draw();

	/*
	 * Sets the brightness of the display
	 */
	void SetBrightness(uint8_t brightness);

	/*
	 * Callback for command parser
	 */
	cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream);
private:
   GraphicsEngine* m_gfx_engine;
   RealTimeClock* m_rtc;
   HabitManager* m_habit_manager;

   static const uint8_t MAX_BRIGHTNESS{5};
   uint8_t m_brightness{1};
};


#endif /* SRC_DISPLAYCONTROLLER_H_ */
