
#include "config.h"
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include "slider_stepper.h"
//Global variables

namespace slider
{

StepperNoTick stepper(PIN_STEPPER_A1, PIN_STEPPER_A2, PIN_STEPPER_B1, PIN_STEPPER_B2, PIN_ENDSTOP,PIN_CANCEL,STEPS_PER_MM,MAX_SPEED,MAX_STEPS);

void setup()
{
    Serial.begin(115200);

}

void loop()
{
    
}


}//namespace slider
