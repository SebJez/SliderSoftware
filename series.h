#ifndef series_h
#define series_h

#include "definitions.h"
#include "lcd16x2.h"
#include "shutter.h"
#include "motor.h"

class Series
{
private:
    Display* display_;
    Shutter* shutter_;
    Motor* motor_;
    long start_pos_;
    long stop_pos_;
    unsigned long step_;
    unsigned long af_time_;
    unsigned long shutter_time_;
    unsigned long dwell_before_;
    unsigned long dwell_after_;
    float speed_;
public:
    Series(Display* display, Shutter* shutter, Motor* motor,\
     long start_pos, long stop_pos, unsigned long step,\
      unsigned long af_time = DEFAULT_AF_TIME, unsigned long shutter_time = DEFAULT_SHUTTER_TIME,\
       unsigned long dwell_before = DEFAULT_DWELL_BEFORE, unsigned long dwell_after = DEFAULT_DWELL_AFTER, float speed = DEFAULT_SPEED);
    
    bool run();
};

Series::Series(Display* display, Shutter* shutter, Motor* motor,\
     long start_pos, long stop_pos, unsigned long step,\
      unsigned long af_time = DEFAULT_AF_TIME, unsigned long shutter_time = DEFAULT_SHUTTER_TIME,\
      unsigned long dwell_before = DEFAULT_DWELL_BEFORE, unsigned long dwell_after = DEFAULT_DWELL_AFTER, float speed = DEFAULT_SPEED): \
        display_(display), shutter_(shutter), motor_(motor), step_(step), \
        af_time_(af_time), shutter_time_(shutter_time), dwell_before_(dwell_before), dwell_after_(dwell_after)
{
    if(stop_pos < 0) stop_pos_=
    if(start_pos<0) start_pos_ = 0;
    else start_pos_ = start_pos;

    if(stop_pos > MAX_STEPS) stop_pos_ = MAX_STEPS;
    else stop_pos_ = stop_pos;

    if(speed > MAX_SPEED) speed_ = MAX_SPEED;
    else if (speed < MIN_SPEED) speed_ = MIN_SPEED;
    else speed_ = speed;
}

bool Series::run()
{
    unsigned long steps = (stop_pos_ - start_pos_)/step + 1;
    motor_->setSpeed(speed_);
    display_->writeTopLine(T_SERIES);
    display_->writeBottomLine("");

    motor_->moveTo(start_pos_);

    for(unsigned long i = 1; i<=steps+1; i++)
    {
        display_->writeBottomLine(display_->padRight(String(i)+"/"+String(steps)));
            if(PIN_CANCEL == LOW) return 1;
        delay(dwell_before_);
            if(PIN_CANCEL == LOW) return 1;
        shutter_->af(af_time_);
            if(PIN_CANCEL == LOW) return 1;
        shutter_->shutter(shutter_time_);
            if(PIN_CANCEL == LOW) return 1;
        delay(dwell_after_);
            if(PIN_CANCEL == LOW) return 1;

        if (i < steps) motor_->move(step_);
        else if(i = steps) motor_->moveTo(stop_pos_);

    }
    return 0;
}


#endif