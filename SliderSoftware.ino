#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"
#include <RotaryEncoder.h>
//#include "menu.h"
//#include "setValue.h"
#include "serialCommand.h"

#ifdef LANGUAGE_EN
  #include "language_en.h"
#endif

#ifdef LANGUAGE_PL
  #include "language_pl.h"
#endif

#ifdef REMOTE_SHUTTER
    //#include "shutter.h"
#endif //REMOTE_SHUTTER


Motor stepper = Motor(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2,\
  PIN_ENDSTOP, PIN_CANCEL, STEPS_PER_MM, DEFAULT_SPEED, FLIP_DIRECTION, MAX_STEPS);

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

RotaryEncoder encoder(PIN_ENCODER_A,PIN_ENCODER_B);

SerialCommand serial(&stepper);

//Configuration of interrupts for the rotary encoder


// see https://thewanderingengineer.com/2014/08/11/arduino-pin-change-interrupts/




//Shutter shutter = Shutter(PIN_SHUTTER, SHUTTER_INVERT);

String mainMenuItems[] = {"1", "2", "3"};

Menu mainMenu = Menu(mainMenuItems,3, PIN_ENCODER_PRESS, PIN_CANCEL, &encoder, &lcd);

//SetValue valueSetter = SetValue("Top text", -500L, 500L, 0L,25L, PIN_ENCODER_PRESS, PIN_CANCEL,\
                                 &lcd, &encoder, "mm",2,"minimum","maximum");


void setup()
{
//PCICR |= 0b00000100;  //0b001 - port B, 0b010 - port C, 0b100 - port D
//PCMSK2 |= 0b01100000; //pins 5 and 6
//ISR(PCINT2_vect)
//{
//  encoder.tick();
//}
  //Serial.begin(9600);
}

void loop()
{

    byte program = mainMenu.run();
    Serial.print(program);
    /*
  serial.run();
    /*byte program = mainMenu.run();
    switch (program)
    {
    case 0x00:
      //RUN MANUAL CONTROL
      break;
    
    case 0x01:
      //HOME
      break;

    case 0x02:
      //PREPARE SHOOT
      break;

    case 0xFF:
      //EXIT
      break;
    }*/
}
