#ifndef definitions_h
#define definitions_h
//---------------------------------------------------------------
//--CONFIG
//---------------------------------------------------------------

//LANGUAGE:

#include "language_en.h"    //ENGLISH
//#include "language_pl.h"  //POLISH

#ifdef REMOTE_SHUTTER
    #define SHUTTER_INVERT false //set to true if shutter triggers on LOW
#endif //REMOTE_SHUTTER

#define USB_SERIAL
#define REMOTE_SHUTTER
#define LCD_16x2
//#define LCD_BACKLIGHT
#ifdef LCD_BACKLIGHT
    #define LCD_BACKLIGHT_ANALOG
    #define LCD_BACKLIGHT_DIGITAL
#endif //LCD_BACKLIGHT

#define STEPS_PER_MM 25.f // screw pitch / steps per rotation
#define MANUAL_STEPS {1,5,25,125,1250}
#define DEFAULT_SPEED 10.f  //in mm/s

#define SOFTWARE_ENDSTOPS
#ifdef SOFTWARE_ENDSTOPS
    #define SLIDER_LENGHT_MM  200f
#endif //SOFTWARE_ENDSTOPS

//---------------------------------------------------------------
//--PINS
//---------------------------------------------------------------
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 5
#define PIN_ENCODER_PRESS 4
#define PIN_CANCEL 3
#define PIN_ENDSTOP 2

#ifdef LCD_16x2
    #define PIN_LCD_RS 7
    #define PIN_LCD_E  8
    #define PIN_LCD_D4 9
    #define PIN_LCD_D5 10
    #define PIN_LCD_D6 11
    #define PIN_LCD_D7 12
#endif //LCD_16x2

#ifdef LCD_BACKLIGHT
    #define PIN_LCD_BACKLIGHT
#endif //PIN_LCD_BACKLIGHT

#ifdef REMOTE_SHUTTER
    #define PIN_SHUTTER A1
    #define PIN_AF  A0
#endif //REMOTE_SHUTTER

#define PIN_STEPPER_A1 A3
#define PIN_STEPPER_A2 A2
#define PIN_STEPPER_B1 A5
#define PIN_STEPPER_B2 A4


#endif
