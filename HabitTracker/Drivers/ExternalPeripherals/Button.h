/*
 * Button.h
 *
 *  Created on: Apr 14, 2021
 *      Author: keisu
 *
 *  For button that is normally HIGH and goes LOW when pressed
 */

#ifndef EXTERNALPERIPHERALS_BUTTON_H_
#define EXTERNALPERIPHERALS_BUTTON_H

#include <cstdint>

class Button
{
public:
	bool IsPressed(bool gpioIsSet);
private:
	uint16_t m_state{UINT16_MAX};
};


#endif /* EXTERNALPERIPHERALS_BUTTON_H_ */
