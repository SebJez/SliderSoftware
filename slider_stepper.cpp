#ifndef slider_stepper_cpp
#define slider_stepper_cpp
#include "slider_stepper.h"
namespace slider
{
Stepper::Stepper(Pin pin_A1,Pin pin_A2,Pin pin_B1,Pin pin_B2, Pin pin_endstop, Pin pin_cancel,\
                      float steps_per_mm,float speed_mm_per_s,long max_step):
                    pin_A1_(pin_A1),
                    pin_A2_(pin_A2),
                    pin_B1_(pin_B1),
                    pin_B2_(pin_B2),
                    pin_endstop_(pin_endstop),
                    pin_cancel_(pin_cancel),
                    steps_per_mm_(steps_per_mm),
                    max_step_(max_step)
{
    pinMode(pin_A1_,OUTPUT);
    pinMode(pin_A2_,OUTPUT);
    pinMode(pin_B1_,OUTPUT);
    pinMode(pin_B2_,OUTPUT);
    current_step_ = 0;
    current_phase_ = 0;
    interval_ms_ = 1000.f/steps_per_mm_/speed_mm_per_s;
    flag_ = OK_FLAG;
}

long Stepper::getStep()
{
    return current_step_;
}

float Stepper::getPosition()
{
    return current_step_/steps_per_mm_;
}

float Stepper::setSpeed(float milimetres_per_second)
{
    interval_ms_ = 1000.f/steps_per_mm_/milimetres_per_second;
    return 1000.f/steps_per_mm_/interval_ms_;
}

float Stepper::getSpeed()
{
    return 1000.f/steps_per_mm_/interval_ms_;
}

void Stepper::setState(unsigned char state)
{
    digitalWrite(pin_A1_, (state & 0b01));
    digitalWrite(pin_A2_, ~(state & 0b01));
    digitalWrite(pin_B1_, (state & 0b10));
    digitalWrite(pin_B2_, ~(state & 0b10));
}
void Stepper::stepBack()
{
    switch(current_phase_ &= 0b11)
        {
        case 0b00:
            setState(0b10);
            break;
        case 0b01:
            setState(0b00);
            break;
        case 0b10:
            setState(0b11);
            break;
        case 0b11:
            setState(0b01);
            break;
        }
        --current_phase_;
        --current_step_;
}
void Stepper::stepForward()
{
    switch (current_phase_ &= 0b11)
        {
        case 0b00:
            setState(0b01);
            break;
        case 0b01:
            setState(0b11);
            break;
        case 0b10:
            setState(0b00);
            break;
        case 0b11:
            setState(0b10);
            break;
        }
        ++current_phase_;
        ++current_step_;
}
long Stepper::moveBy(long steps, bool software_endstops = true)
{
    if(software_endstops)
    {
        if(current_step_+steps > max_step_) steps = max_step_ - current_step_;
        if(current_step_ + steps < 0) steps = -current_step_;
    }
    
    flag_ = OK_FLAG;

    attachInterrupt(pin_endstop_,onEndstop);
    attachInterrupt(pin_cancel_,onCancel);


    while (steps < 0 && flag_ == OK_FLAG)
    {
        stepForward();
        ++steps;
    }
    while (steps>0 && flag_ == OK_FLAG)
    {
        stepBack();
        --steps;      
    }
    detachInterrupt(pin_cancel_);
    detachInterrupt(pin_endstop_);

    return current_step_;
 
}

long Stepper::moveTo(long position_steps, bool software_endstops = true)
{
    return moveBy(current_step_+position_steps, software_endstops);
}

float Stepper::moveBy(float milimetres, bool software_endstops = true)
{
    return moveBy(milimetres*steps_per_mm_, software_endstops)/steps_per_mm_;
}

float Stepper::moveTo(float position_mm, bool software_endstops = true)
{
    return moveTo(position_mm*steps_per_mm_, software_endstops)/steps_per_mm_;
}

long Stepper::home()
{
    moveBy(-max_step_,false);
    if(flag_ = ENDSTOP_FLAG)
        current_step_ = 0;
    return current_step_;
}

long Stepper::homeOnMax()
{
    moveBy(max_step_,false);
    if(flag_ = ENDSTOP_FLAG)
        current_step_ = max_step_;
    return current_step_;
}

inline StepperFlag Stepper::getFlag()
{
    return flag_;
}

inline float Stepper::stepsToMm(long steps) const
{
    return (float)steps/steps_per_mm_;
}
inline long Stepper::mmToSteps(float milimetres) const;
{
    return milimetres*steps_per_mm_;
}
}//namespace slider
#endif
