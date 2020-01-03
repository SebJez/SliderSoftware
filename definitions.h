#ifndef definitions_h
#define definitions_h
//---------------------------------------------------------------
//--CONFIG
//---------------------------------------------------------------

#define LANGUAGE_EN
//#define LANGUAGE_PL

#ifdef LANGUAGE_EN
    #include "language_en.h"
#else
#ifdef LANGUAGE_PL
    #include "language_pl.h"
#endif
#endif

// UNUSED:
//
// #define REMOTE_SHUTTER
// 
// #ifdef REMOTE_SHUTTER
//     #define SHUTTER_INVERT false //set to true if shutter triggers on LOW
// #endif //REMOTE_SHUTTER
// 
// #define USB_SERIAL
// #define REMOTE_SHUTTER
// #define LCD_16x2
// //#define LCD_BACKLIGHT
// #ifdef LCD_BACKLIGHT
//     #define LCD_BACKLIGHT_ANALOG
//     #define LCD_BACKLIGHT_DIGITAL
// #endif //LCD_BACKLIGHT

#define STEPS_PER_MM 50L //steps per rotation / screw pitch
#define DEFAULT_SPEED 2.f  //in mm/s
#define MAX_SPEED 2.f
#define MIN_SPEED 0.02f
#define MAX_STEPS 15000L
#define SOFTWARE_ENDSTOPS


#ifdef SOFTWARE_ENDSTOPS

    #define ENABLE_ENDSTOPS true
#else
    #define ENABLE_ENDSTOPS false
#endif //SOFTWARE_ENDSTOPS

//---------------------------------------------------------------
//--PINS
//---------------------------------------------------------------
#define PIN_ENCODER_A 5 //if you change these pins, you need to change
#define PIN_ENCODER_B 6 //the interrupt configuration in SliderSoftware.ino 


#define PIN_ENCODER_PRESS 4
#define PIN_CANCEL 3
#define PIN_ENDSTOP 2

//#ifdef LCD_16x2
    #define PIN_LCD_RS 7
    #define PIN_LCD_E  8
    #define PIN_LCD_D4 9
    #define PIN_LCD_D5 10
    #define PIN_LCD_D6 11
    #define PIN_LCD_D7 12
//#endif //LCD_16x2

//#ifdef LCD_BACKLIGHT
    #define PIN_LCD_BACKLIGHT
//#endif //PIN_LCD_BACKLIGHT

//#ifdef REMOTE_SHUTTER
    #define PIN_SHUTTER A1
    #define PIN_AF  A0
//#endif //REMOTE_SHUTTER

#define PIN_STEPPER_A1 A5
#define PIN_STEPPER_A2 A4
#define PIN_STEPPER_B1 A3
#define PIN_STEPPER_B2 A2

//---------------------------------------------------------------
//-DEFAULT-TIMING
//---------------------------------------------------------------
#define DEFAULT_AF_TIME 500L
#define DEFAULT_SHUTTER_TIME 100L
#define DEFAULT_DWELL_BEFORE 100L
#define DEFAULT_DWELL_AFTER 500L

#endif
