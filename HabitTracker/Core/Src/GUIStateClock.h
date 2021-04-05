/*
 * GUIStateClock.h
 *
 *  Created on: Mar 30, 2021
 *      Author: keisu
 */

#ifndef SRC_GUISTATECLOCK_H_
#define SRC_GUISTATECLOCK_H_

#include "GUIStateBase.h"

class GUIStateClock : public GUIStateBase
{
public:
	GUIStateClock(GraphicsEngine* gfx_engine, GUIControllerTask* controller) : GUIStateBase(gfx_engine, controller) {};
	void UIDraw() override;
	void OnLoaded() override;
private:
	void DrawTime();
};



#endif /* SRC_GUISTATECLOCK_H_ */
