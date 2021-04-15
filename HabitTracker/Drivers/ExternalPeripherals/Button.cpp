/*
 * Button.cpp
 *
 *  Created on: Apr 14, 2021
 *      Author: keisu
 */
#include "Button.h"

bool Button::IsPressed(bool gpioIsSet)
{
	m_state = (m_state << 1 ) | (gpioIsSet ? 1 : 0) | 0xe000;

	if(m_state==0xf000)
	{
		return true;
	}else
	{
		return false;
	}
}

