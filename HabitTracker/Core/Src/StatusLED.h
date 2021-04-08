/*
 * StatusLED.h
 *
 *  Created on: Apr 6, 2021
 *      Author: keisu
 */

enum class LEDState_t
{
   Ok,
   Error
};

class StatusLED
{
public:
	static void SetState(LEDState_t state);
   static LEDState_t GetState();
private:
   static LEDState_t m_state;
};

