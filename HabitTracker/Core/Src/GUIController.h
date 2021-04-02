/*
 * GUI.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef SRC_GUICONTROLLER_H_
#define SRC_GUICONTROLLER_H_


enum class GUIState : uint32_t {
	MAIN_CLOCK,
	SET_TIME,
	HABITS
};

class GUIController 
{
public:
	bool AddState(GUIStateBase *state_ptr, GUIState state_enum);
	void SetState(GUIState new_state);
	void UIDraw();
	void UILeft() { m_curr_state->UILeft(); };
	void UIRight() { m_curr_state->UIRight();	};
	void UISelect() { m_curr_state->UISelect(); };

private:
	static const size_t MAX_NUM_STATES = 32;
	GUIStateInterface *m_curr_state;
	GUIStateInterface *m_states[MAX_NUM_STATES];
};

#endif /* SRC_GUICONTROLLER_H_ */
