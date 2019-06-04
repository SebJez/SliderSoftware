#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"
#include "readKnob.h"
#include <Encoder.h>

Motor stepper = Motor(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2,\
  PIN_ENDSTOP, PIN_CANCEL, STEPS_PER_MM, DEFAULT_SPEED, FLIP_DIRECTION, ENABLE_ENDSTOPS, MAX_STEPS);

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

Encoder encoder = Encoder(PIN_ENCODER_A, PIN_ENCODER_B);

Shutter shutter = Shutter(PIN_SHUTTER, PIN_AF, SHUTTER_INVERT);

#include "menu.h"

pinMode(PIN_ENCODER_PRESS, INPUT_PULLUP);
pinMode(PIN_CANCEL, INPUT_PULLUP);

// -- INCLUDE SUBPROGRAMS HERE-- //
#include "manualControl.h"
#include "home.h"
#include "setup.h"

// -- MAIN MENU -- //
MenuItem[] subprograms = \
[
  MenuItem(T_MANUAL_CONTROL, &manualControl()),
  MenuItem(T_HOME, &home()),
  MenuItem(T_SETUP_MENU, &setupMenu()),
]

Menu mainMenu = Menu(&lcd, &encoder, PIN_ENCODER_PRESS, PIN_CANCEL, &subprograms)


void loop()
{
  mainMenu.run();
}


