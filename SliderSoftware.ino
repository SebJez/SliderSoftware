#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"

#ifdef REMOTE_SHUTTER
    #include "shutter.h"
#endif //REMOTE_SHUTTER


Motor stepper = Motor(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2,\
  STEPS_PER_MM, DEFAULT_SPEED, FLIP_DIRECTION, ENABLE_ENDSTOPS, MAX_STEPS);

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

#ifdef USE_AF
Shutter shutter = Shutter(PIN_SHUTTER, PIN_AF, SHUTTER_INVERT);
#else
Shutter shutter = Shutter(PIN_SHUTTER, SHUTTER_INVERT);
#endif //USE_AF


void setup()
{

}

void loop()
{

}