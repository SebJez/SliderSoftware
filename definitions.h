#pragma once

//---------------------------------------------------------------
//--CONFIG
//---------------------------------------------------------------
#define REMOTE_SHUTTER
#define USB_SERIAL
#define ENCODER
#define LCD_16x2
//#define LCD_BACKLIGHT
#ifdef LCD_BACKLIGHT
    #define LCD_BACKLIGHT_ANALOG
    #define LCD_BACKLIGHT_DIGITAL
#endif //LCD_BACKLIGHT
#define STEPS_PER_ROTATION 200
#define STEPS_PER_MM 1600 //STEPS_PER_ROTATION * SCREW_PITCH

//---------------------------------------------------------------
//--PINS
//---------------------------------------------------------------
#ifdef  ENCODER
    #define PIN_ENCODER_A
    #define PIN_ENCODER_B
    #define PIN_ENCODER_PRESS
#endif //ENCODER

#define PIN_CANCEL
#define PIN_ENDSTOP

#ifdef LCD_16x2
    #define PIN_LCD_RS
    #define PIN_LCD_RW
    #define PIN_LCD_E
    #define PIN_LCD_D4
    #define PIN_LCD_D5
    #define PIN_LCD_D6
    #define PIN_LCD_D7
#endif //LCD_16x2

#ifdef LCD_BACKLIGHT
    #define PIN_LCD_BACKLIGHT
#endif //PIN_LCD_BACKLIGHT

#ifdef REMOTE_SHUTTER
    #define PIN_SHUTTER
    #define PIN_AF
#endif //REMOTE_SHUTTER

#define PIN_STEPPER_A1
#define PIN_STEPPER_A2
#define PIN_STEPPER_B1
#define PIN_STEPPER_B2


//------------------------------------------------------------------
//--LIBRARIES
//------------------------------------------------------------------
#ifdef ENCODER
    #define ENCODER_LIBRARY
#endif //ENCODER
