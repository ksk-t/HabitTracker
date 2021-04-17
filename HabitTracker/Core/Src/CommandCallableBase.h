/*
 * CommandCallable.h
 *
 *  Created on: Apr 17, 2021
 *      Author: keisu
 */

#ifndef SRC_COMMANDCALLABLE_H_
#define SRC_COMMANDCALLABLE_H_

#include "IOStreamBase.h"
#include <cstddef>
#include <cstdint>

enum class cmd_status_t
{
	Ok,
	InvalidCode
};

class CommandCallableBase
{
protected:
	virtual ~CommandCallableBase() {};
private:
	virtual void CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream) {};
};



#endif /* SRC_COMMANDCALLABLE_H_ */
