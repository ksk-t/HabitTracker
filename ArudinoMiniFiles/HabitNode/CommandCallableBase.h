/*
 * CommandCallable.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef SRC_COMMANDCALLABLE_H_
#define SRC_COMMANDCALLABLE_H_

#include "IOStreamBase.h"
#include <stddef.h>
#include <stdint.h>

enum class cmd_status_t
{
	Ok,
	InvalidCode,
	InvalidParamter
};

class CommandCallableBase
{
protected:
	virtual ~CommandCallableBase() {};
public:
	virtual cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code) {return cmd_status_t::Ok; };
};



#endif /* SRC_COMMANDCALLABLE_H_ */
