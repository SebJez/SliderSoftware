
#include "config.h"
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include "slider_stepper.h"
#include "slider_display.h"
#include "slidder_shutter.h"

//Global variables


namespace slider
{

Display g_display(PIN_LCD_E,PIN_LCD_RS,PIN_LCD_D4,PIN_LCD_D5,PIN_LCD_D6,PIN_LCD_D7);
RotaryEncoder g_encoder(PIN_ENCODER_A,PIN_ENCODER_B);
Shutter g_shutter(PIN_SHUTTER,PIN_AF,SHUTTER_INVERT);

void setup()
{
    Serial.begin(115200);

}

void loop()
{
    
}


}//namespace slider
