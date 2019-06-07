#ifndef manualControl_h
#define manualControl_h
#include "menu.h"
#include "motor.h"

namespace manualControl
{
    long steps[] = MANUAL_STEPS;
    long sizeofSteps = sizeof(steps)/sizeof(steps[0]);
    int motor_step_index = 0;
    int current_step_index = 0;
    bool exit_flag = false;

    // -- STEP SELECTION -- //
    void stepUp()
    {
        if(current_step_index + 1 < sizeofSteps)
            current_step_index++;
    }
    void stepDown()
    {
        if(current_step_index >0)
            current_step_index--;
    }
    void stepOK()
    {
        motor_step_index = current_step_index;
        exit_flag = true;
    }
    void stepCancel()
    {
        exit_flag = true;
    }

    //0123456789ABCDEF
    //      000.00 mm
    void step()
    {
        current_step_index = motor_step_index;
        while(!exit_flag)
        {
            lcd->writeTopLine(T_MANUAL_SET_STEP);
            lcd->writeBottomLine("      "+String(steps[current_step_index]/STEPS_PER_MM,2)+" mm");
            readKnob(&encoder, PIN_ENCODER_PRESS, PIN_CANCEL, &stepUp, &stepDown, &stepOK, &stepCancel);
        }
        exit_flag = false;

    }


    // -- MOVE -- //
    
    long steps_to_move = 0

    void moveUp()
    {
        if(steps_to_move + position + 1 < MAX_STEPS)
            steps_to_move++;
    }

    void moveDown()
    {
        if(steps_to_move + position - 1 >= 0)
            steps_to_move--;

    }

    void moveOK()
    {
        stepper.move(steps_to_move);
    }

    void moveCancel()
    {
        exit_flag = true;
    }

    void move()
    {
        long position = stepper.getStep();
        float position_mm = stepper.getStep()/STEPS_PER_MM;

        while (!exit_flag)
        {
            lcd->writeTopLine(T_MANUAL_POSITION+" "+String(position_mm,2)+"mm");
            
            float steps_to_move_mm = steps_to_move / STEPS_PER_MM;
            lcd->writeBottomLine(String(steps_to_move_mm,2)+"mm    "+\
              String(position_mm+steps_to_move_mm,2)+"mm");

            readKnob(&encoder, PIN_ENCODER_PRESS, PIN_CANCEL, \
              &moveUp, &moveDown, &moveOK, &moveCancel);
        }
        exit_flag = false;
    }


    // -- SUBMENU -- //


    MenuItem* submenu_items = \
    [
        MenuItem(T_MANUAL_MOVE, &move),
        MenuItem(T_MANUAL_STEP, &step)
    ];

    Menu submenu = Menu(&lcd, &encoder, PIN_ENCODER_PRESS, PIN_CANCEL, submenu_items);

    void main()
    {
        submenu.run();
    }
}
#endif