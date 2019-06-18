#ifndef config_h
#define config_h

// UI Language -----------
//#include "language_pl.h"
#include "language_en.h"

// Geometry --------------
#define STEPS_PER_MM 25.f
#define MAX_SPEED 10.f  //in mm/s
#define MAX_STEPS 5000L //length of slider in steps

// Pinout ----------------
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 5
#define PIN_ENCODER_PRESS 4
#define PIN_CANCEL 3
#define PIN_ENDSTOP 2

#define PIN_LCD_RS 7
#define PIN_LCD_E  8
#define PIN_LCD_D4 9
#define PIN_LCD_D5 10
#define PIN_LCD_D6 11
#define PIN_LCD_D7 12

#define PIN_SHUTTER A1
#define PIN_AF  A0
    
#define PIN_STEPPER_A1 A3
#define PIN_STEPPER_A2 A2
#define PIN_STEPPER_B1 A5
#define PIN_STEPPER_B2 A4

#endif