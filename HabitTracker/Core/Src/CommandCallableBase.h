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
public:
	virtual cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code, IOStreamBase* iostream) {return cmd_status_t::Ok; };
};



#endif /* SRC_COMMANDCALLABLE_H_ */
