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
    #define USE_AF
#endif //REMOTE_SHUTTER

#define USB_SERIAL

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
#define PIN_ENCODER_A
#define PIN_ENCODER_B
#define PIN_ENCODER_PRESS
#define PIN_CANCEL
#define PIN_ENDSTOP

#ifdef LCD_16x2
    #define PIN_LCD_RS 1
    #define PIN_LCD_E  2
    #define PIN_LCD_D4 4
    #define PIN_LCD_D5 3
    #define PIN_LCD_D6 5
    #define PIN_LCD_D7 6
#endif //LCD_16x2

#ifdef LCD_BACKLIGHT
    #define PIN_LCD_BACKLIGHT
#endif //PIN_LCD_BACKLIGHT

#ifdef REMOTE_SHUTTER
    #define PIN_SHUTTER
#endif //REMOTE_SHUTTER

#ifdef USE_AF
    #define PIN_AF
#endif

#define PIN_STEPPER_A1
#define PIN_STEPPER_A2
#define PIN_STEPPER_B1
#define PIN_STEPPER_B2


//------------------------------------------------------------------
//--LIBRARIES AND INCLUDES
