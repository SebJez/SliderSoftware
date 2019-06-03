#include "definitions.h"
#include "lcd16x2.h"
#include "motor.h"

Motor stepper = Motor(PIN_STEPPER_A1,PIN_STEPPER_A2,PIN_STEPPER_B1,PIN_STEPPER_B2,STEPS_PER_MM,DEFAULT_SPEED,FLIP_DIRECTION, ENABLE_ENDSTOPS, MAX_STEPS);
Display lcd = Display();
void setup()
{

}

void loop()
{

}