/*
 * GUI.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef SRC_GUICONTROLLER_H_
#define SRC_GUICONTROLLER_H_

#include "GUIStateBase.h"

enum class GUIState : uint32_t {
	Clock,
	SET_TIME,
	HABITS
};

class GUIControllerTask
{
public:
	bool AddState(GUIStateBase *state_ptr, GUIState state_enum);
	void SetState(GUIState new_state);
	void Initialize();
	void Run();
	void UIDraw();
	void UILeft() { m_curr_state->UILeft(); };
	void UIRight() { m_curr_state->UIRight();	};
	void UISelect() { m_curr_state->UISelect(); };

	uint32_t RefreshInterval{UINT32_MAX};
private:
	static const size_t MAX_NUM_STATES = 32;
	GUIStateBase *m_curr_state = nullptr;
	GUIStateBase *m_states[MAX_NUM_STATES];
};

#endif /* SRC_GUICONTROLLER_H_ */
