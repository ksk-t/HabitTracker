#include "LEDTLC5955.h"
#include "CommandParser.h"

#define INPUT_BUFFER_SIZE 64
uint8_t input_buffer[INPUT_BUFFER_SIZE];

LEDTLC5955 tlc{};
CommandParser cmd_parser{};

#define CMD_SET_LED 0
uint8_t setled[] = "setled";

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  // Configure TLC Driver
  tlc.SetMaxCurrent(1, 1, 1);
  tlc.SetGlobalBrightness(10, 10, 10);
  TLC5955_function_t function;
  function.display_timing_reset_enable = true;
  tlc.SetFunction(function);
  tlc.UpdateControlSettings();
  
  Color_t color{0, 5000, 10000};
  tlc.SetLed(13, color);

  // Setup comamands
  cmd_parser.RegisterModule(Module_t::LEDController, &tlc);
  Command_t cmd;
  cmd.Module = Module_t::LEDController;
  cmd.Name = setled;
  cmd.Code = CMD_SET_LED;
  cmd_parser.RegisterCommand(cmd);
}

// the loop function runs over and over again forever
void loop() {
  // Should never get here
  if (Serial.available() > 0)
  {
    size_t bytes_read = Serial.readBytesUntil('\n', input_buffer, INPUT_BUFFER_SIZE);
    if (0 < bytes_read)
    {
      cmd_parser.Execute(input_buffer, INPUT_BUFFER_SIZE);
    }
  }
  
  tlc.UpdateLED();
  tlc.SendColorBuffer();
  delay(10);
}

 
