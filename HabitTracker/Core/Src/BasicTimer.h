/*
 * BasicTimer.h
 *
 *  Created on: Apr 25, 2021
 *      Author: keisu
 */

#ifndef SRC_BASICTIMER_H_
#define SRC_BASICTIMER_H_


#include <cstdint>

class BasicTimer
{
public:
	/*
	 * Starts timer
	 *
	 * @param initial_tick Tick count at the start of the timer
	 */
	void Start(uint32_t inital_tick, uint32_t interval);

	/*
	 * Determines if timer has expired
	 *
	 * @param uint32_t tick Current system tick value
	 *
	 * @return True if timer has expired, false otherwise
	 */
	bool HasExpired(uint32_t tick);
private:
   uint32_t m_initial_tick{0};
   uint32_t m_interval{0};
};




#endif /* SRC_BASICTIMER_H_ */
