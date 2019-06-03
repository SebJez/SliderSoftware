#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"

#ifdef REMOTE_SHUTTER
    #include "shutter.h"
#endif //REMOTE_SHUTTER

#ifdef LCD_16x2
    #include "lcd16x2.h"
#endif //LCD_16x2


Motor stepper = Motor(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2,\
  STEPS_PER_MM, DEFAULT_SPEED, FLIP_DIRECTION, ENABLE_ENDSTOPS, MAX_STEPS);

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

void setup()
{

}

void loop()
{

}