#ifndef slider_program_h
#define slider_program_h
#include "config.h"
#include "slider_stepper.h"
#include "slider_shutter.h"
namespace slider
{

class Program
{
private:
    long start_step_;
    long stop_step_;
    long photo_every_steps_;
    long wait_before_photo_ms_;
    long wait_after_photo_ms_;
    long shutter_time_ms_;
    long af_time_ms_;
    Stepper* stepper_;
    Shutter* shutter_
public:
    Program(StepperNoTick* stepper, Shutter* shutter, long start_step, long stop_step, long photo_every_steps, \
            unsigned long wait_before_photo_ms = DEFAULT_WAIT_BEFORE_PHOTO_MS, unsigned long wait_after_photo_ms = DEFAULT_WAIT_AFTER_PHOTO_MS, \
            unsigned long shutter_time_ms=DEFAULT_SHUTTER_WAIT, unsigned long af_time_ms=DEFAULT_AF_WAIT);
    bool run();
};

Program::Program(StepperNoTick* stepper, Shutter* shutter,long start_step, long stop_step, long photo_every_steps, \
            unsigned long wait_before_photo_ms = DEFAULT_WAIT_BEFORE_PHOTO_MS, unsigned long wait_after_photo_ms = DEFAULT_WAIT_AFTER_PHOTO_MS, \
            unsigned long shutter_time_ms=DEFAULT_SHUTTER_WAIT, unsigned long af_time_ms=DEFAULT_AF_WAIT) :
            stepper_(stepper),
            shutter_(shutter),
            start_step_(start_step),
            stop_step_(stop_step),
            photo_every_steps_(photo_every_steps),
            wait_before_photo_ms_(wait_before_photo_ms),
            wait_after_photo_ms_(wait_after_photo_ms),
            shutter_time_ms_(shutter_time_ms),
            af_time_ms_(af_time_ms)
{

bool Program::run()
{
    bool dir = (start_step_ < stop_step_);
    long step = stepper_->moveTo(start_step_);
    while(dir ? (step <= stop_step_) : (step >= stop_step))
    {
        delay(wait_before_photo_ms_);
        shutter_->afShutter(af_time_ms_,shutter_time_ms_);
        delay(wait_after_photo_ms_);
        step = stepper_->moveBy(dir ? photo_every_steps_ : -photo_every_steps_);
        if (stepper_->getFlag() != OK_FLAG) return false;
    }
    return true;
}

}
#endif