/*
 * Status.h
 *
 *  Created on: Apr 6, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_STATUS_H_
#define EXTERNALPERIPHERALS_STATUS_H_

enum class Status_t
{
	OK      = 0,
	ERROR   = 1 << 0,
	BUSY    = 1 << 1,
	TIMEOUT = 1 << 2
};

inline Status_t operator|(Status_t a, Status_t b)
{
    return static_cast<Status_t>(static_cast<int>(a) | static_cast<int>(b));
}

inline Status_t& operator |=(Status_t& a, Status_t b)
{
    return a = a | b;
}

#endif /* EXTERNALPERIPHERALS_STATUS_H_ */
