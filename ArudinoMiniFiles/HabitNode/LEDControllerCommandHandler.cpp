#include "LEDControllerCommandHandler.h"
#include "StringUtilities.h"
#include <string.h>
#include "Arduino.h"

cmd_status_t LEDControllerCommandHandler::CommandCallback(uint8_t* buffer, size_t size, uint32_t code)
{
   cmd_status_t status = cmd_status_t::Ok;
  size_t MAX_NUM_ARGS = 5;
  uint32_t args[MAX_NUM_ARGS];

  memset(args, 0, MAX_NUM_ARGS);
  StringUtilities::SplitToUint(buffer, size, ',', args, MAX_NUM_ARGS);
  Serial.print("\nCommand: ");
  Serial.print(args[0]);
  Serial.print(",");
  Serial.print(args[1]);
  Serial.print(",");
  Serial.print(args[2]);
  Serial.print(",");
  Serial.print(args[3]);
  

  Color_t new_color{args[1], args[2], args[3]};
  m_handler->SetLed(args[0], new_color);
  return status;
}
