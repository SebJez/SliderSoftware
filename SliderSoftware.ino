
#include "config.h"
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include "slider_stepper.h"
#include "slider_display.h"

//Global variables


namespace slider
{

StepperNoTick g_stepper(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2, PIN_ENDSTOP,PIN_CANCEL,STEPS_PER_MM,MAX_SPEED,MAX_STEPS);
Display g_display(PIN_LCD_E,PIN_LCD_RS,PIN_LCD_D4,PIN_LCD_D5,PIN_LCD_D6,PIN_LCD_D7);


void setup()
{
    Serial.begin(115200);

}

void loop()
{
    
}


}//namespace slider
