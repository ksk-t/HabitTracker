/*
 * GUIController.cpp
 *
 *  Created on: Apr 2, 2021
 *      Author: keisu
 */


#include "GUIControllerTask.h"
#include "Logger.h"

static const std::string MODULE_NAME = "GUIController";

GUIControllerTask::GUIControllerTask()
{
	m_states.fill(nullptr);
}

bool GUIControllerTask::AddState(GUIStateBase* state_ptr, GUIState state_enum)
{
	uint32_t state_int = static_cast<uint32_t>(state_enum);
	if (state_int >= m_states.size())
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "AddState: Failed to add state. Max number of states reached";
		return false;
	}

	m_states[state_int] = state_ptr;
	return true;
}

void GUIControllerTask::SetState(GUIState new_state)
{
	if (m_states[static_cast<uint32_t>(new_state)] != nullptr)
	{
		m_curr_state = m_states[static_cast<uint32_t>(new_state)];
		m_curr_state->OnLoaded();
	}else
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "SetState: State enum has no state referenced to it";
	}
}

void GUIControllerTask::UIDraw()
{
	if (m_curr_state != nullptr)
	{
		m_curr_state->UIDraw();
	}else
	{
		Logger(LoggingLevel::Error, MODULE_NAME).Get() << "UIDraw: current state null";
	}

};

void GUIControllerTask::Run()
{
	// Read inputi tespting test
	for(;;)
	{
		// Add timer to trigger ui to redraw?
	}
}

