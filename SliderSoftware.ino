#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"

#include <Encoder.h>

Motor stepper = Motor(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2,\
  PIN_ENDSTOP, PIN_CANCEL, STEPS_PER_MM, DEFAULT_SPEED, FLIP_DIRECTION, ENABLE_ENDSTOPS, MAX_STEPS);

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

Encoder encoder = Encoder(PIN_ENCODER_A, PIN_ENCODER_B)

Shutter shutter = Shutter(PIN_SHUTTER, PIN_AF, SHUTTER_INVERT);

typedef struct s_menuItem {String name, byte(*subprogram)()} MenuItem;

pinMode(PIN_ENCODER_PRESS, INPUT_PULLUP);
pinMode(PIN_CANCEL, INPUT_PULLUP);

// -- INCLUDE SUBPROGRAMS HERE-- //
#include "manualControl.h"
#include "home.h"
#include "setup.h"

MenuItem[] main_menu = [
  MenuItem(T_MANUAL_CONTROL, &manualControl),
  MenuItem(T_SETUP_SESSION, &setupSession),
  MenuItem(T_HOME_SLIDER, &homeSlider),
  MenuItem(T_MOVE_SLIDER, &moveSlider)
]

// -- MAIN MENU -- //
byte current_item = 0;
byte menuLenght = sizeof(main_menu) / sizeof (main_menu[0]);
encoder.write(0);
void loop()
{
  // -- ENCODER  -- //
  byte jump = encoder.read()/4;
  while(jump > 0)
  {
    jump--;
    if(current_item < menuLenght - 1)
    {
      current_item++;
      lcd.writeTopLine(">"+main_menu[current_item].name);

      if(current_item < menuLenght - 1)
        lcd.writeBottomLine(" "+main_menu[current_item+1].name);
      else
        lcd.writeBottomLine(" ");
      
      
    }
  
  }
  while (jump < 0)
  {
    jump++;
    if(current_item > 0)
    {
      current_item--;
      lcd.writeTopLine(">"+main_menu[current_item].name);

      if(current_item < menuLenght - 1)
        lcd.writeBottomLine(" "+main_menu[current_item+1].name);
      else
        lcd.writeBottomLine(" ");

    }
  }
  if(digitalRead(PIN_ENCODER_PRESS)==LOW)
  {
    main_menu[currentItem].subprogram();
  }
  
}
