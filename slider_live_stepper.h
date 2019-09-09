#ifndef slider_live_stepper_h
#define slider_live_stepper_h
#include "config.h"
#include "slider_stepper.h"
#include "slider_display.h"
#include <RotaryEncoder.h>
#include "slider_shutter.h"

namespace slider
{
typedef const unsigned char Pin;

class LiveStepper
private:
    Stepper* stepper_;
    Display* display_;
    RotaryEncoder* encoder_;
    Pin ok_pin_;
    Pin cancel_pin_;

public:
    LiveStepper(Stepper* stepper, Display* display, RotaryEncoder* encoder, Pin ok_pin, Pin cancel_pin);
    void run();
};

LiveStepper::LiveStepper(Stepper* stepper, Display* display, RotaryEncoder* encoder, Pin ok_pin, Pin cancel_pin) : \
    stepper_(stepper), \
    display_(display), \
    encoder_(encoder), \
    ok_pin_(ok_pin),   \
    cancel_pin_(cancel_pin)
{

}

void LiveStepper::run()
{
    bool exit_flag = false;
    bool update_display = true;
    long stepper_position = stepper_->getStep();
    long encoder_position = 0;
    long goToStep = 0;
    unsigned long last_step = millis();
    encoder_->setPosition(stepper_position);

    while(stepper_->getFlag == OK_FLAG)
    {
        encoder_->tick();
        unsigned long this_step = millis();
        unsigned long interval = this_step - last_step;

        if(encoder_position != encoder->getPosition())
        {
            encoder_position = encoder_->getPosition();
            update_display = true;
        }

        if (stepper_position != stepper_->getStep())
        {
            stepper_position = stepper_->getStep();
            update_display = true;
        }
        
        if(interval > stepper_->interval_ms_ && stepper_position < encoder_position)
        {
            last_step = this_step;
            stepper_->stepForward();
        }
        else if(interval > stepper_->interval_ms_ && stepper_position > encoder_position)
        {
            last_step = this_step;
            stepper_->stepBack();
        }
        
        encoder_->tick();

        if (update_display)
        {
        String top  = display_->pad(T_LIVE_STEPPER_POSITION + \
        display_->formatFloatingPoint(stepper_->stepsToMm(stepper_position),2,false,"","mm"), T_LIVE_STEPPER_POSITION.length());

        String bottom = display_->pad(T_LIVE_ENCODER_POSITION + \
        display_->formatFloatingPoint(stepper_->stepsToMm(encoder_position),2,false,"","mm"), T_LIVE_STEPPER_POSITION.length());

        display_->writeTopLine(top);
        display_->writeBottomLine(bottom);
        }

    }
}



} // namespace slider


#endif
