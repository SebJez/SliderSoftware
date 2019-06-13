#Structure
*  Modules
  * manual
  * setup
  * remote

* Commmon resources
  
  * Stepper
    * class Stepper
      * home
      * moveTo
      * getStep
      * getMax
      * getMin
      * inline stepsToMm
      * inline stepsToHundreths
    * global g_stepper
    * defines
      * stepper pins
      * steps_per_mm

  * Shutter
    * class Shutter
        (copy from previous)
    * global g_shutter

  * Encoder
    * <RotaryEncoder.h>
    * global g_encoder
  
  * Pins
    * global g_pinOk;
    * global g_pinCancel;
  
  * Display
    * class Display (wrapper for LiquidCrystal)
      * writeTopLine
      * writeBottomLine
      * formatting functions
    * global g_display

* UI Elements
   * ListMenu
   * ValueSelector