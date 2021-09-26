#ifndef LEDCONTROLLERCOMMANDHANDLER_H_
#define LEDCONTROLLERCOMMANDHANDLER_H_

#include "CommandCallableBase.h"
#include "LEDTLC5955.h"

class LEDControllerCommandHandler : public CommandCallableBase
{
public:

   LEDControllerCommandHandler(LEDTLC5955 *handler);

   cmd_status_t CommandCallback(uint8_t* buffer, size_t size, uint32_t code);
private:
   LEDTLC5955 *m_handler;  
};

#endif

