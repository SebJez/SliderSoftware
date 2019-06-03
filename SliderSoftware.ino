#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"
#include "menu.h"
#include <Encoder.h>

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

Encoder encoder = Encoder(PIN_ENCODER_A, PIN_ENCODER_B);
MenuItem* currentMenu;

//menus initialisation
auto mainMenu = MainMenu(&lcd);


void setup()
{
    pinMode(PIN_ENCODER_PRESS, INPUT_PULLUP);
    pinMode(PIN_CANCEL, INPUT_PULLUP);
    pinMode(PIN_ENDSTOP, INPUT_PULLUP);
    encoder.write(0);
    int old_position = 0;
    int new_position = 0;
    currentMenu = &mainMenu;
    currentMenu.show();
}

void loop()
{
    new_position = encoder.read()/4;
    while(new_position < old_position)
    {
        currentMenu = currentMenu.action_right();
        new_position++;
    }
    while(new_position > old_position)
    {
        currentMenu = currentMenu.action_left();
        new_position--;
    }
    encoder.write(0)
    if(digitalRead(PIN_ENCODER_PRESS, LOW))
    {
        currentMenu = currentMenu.action_press();
    }
    if (digitalRead(PIN_CANCEL, LOW))
    {
        currrentMenu = currentMenu.action_cancel();
    }

}