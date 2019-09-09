#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RotaryEncoder.h>
#include "config.h"
#include "slider_stepper.h"
#include "slider_display.h"
#include "slider_shutter.h"
#include "slider_live_stepper.h"
//Global variables


namespace slider
{

Display g_display(PIN_LCD_E,PIN_LCD_RS,PIN_LCD_D4,PIN_LCD_D5,PIN_LCD_D6,PIN_LCD_D7);
RotaryEncoder g_encoder(PIN_ENCODER_A,PIN_ENCODER_B);
Shutter g_shutter(PIN_SHUTTER,PIN_AF,SHUTTER_INVERT);
Stepper g_stepper(PIN_STEPPER_A1,PIN_STEPPER_A2,PIN_STEPPER_B1,PIN_STEPPER_B2,PIN_ENDSTOP,PIN_CANCEL,STEPS_PER_MM,10.f,10000);
LiveStepper live(&g_stepper,&g_display,&g_encoder,PIN_ENCODER_PRESS,PIN_CANCEL);

void setup()
{
    Serial.begin(115200);

}

void loop()
{
    live.run();
}


}//namespace slider
