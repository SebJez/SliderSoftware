#ifndef slider_shutter_cpp
#define slider_shutter_cpp
#include "slider_shutter.h"


namespace slider
{

Shutter::Shutter(Pin pin_shutter, Pin pin_af): \
  pin_shutter_(pin_shutter), pin_af_(pin_af)
{
    pinMode(pin_shutter_, OUTPUT);
    pinMode(pin_af_, OUTPUT);

    normal_state_ = (invert ? HIGH : LOW);
    active_state_ = (invert ? LOW : HIGH);

    digitalWrite(pin_shutter_, normal_state_);
    digitalWrite(pin_af_, normal_state_);
}


void Shutter::af(unsigned long af_time_ms = DEFAULT_AF_WAIT) const
{
    digitalWrite(pin_af_, active_state_);
    delay(af_time_ms);
    digitalWrite(pin_af_, normal_state_);
}

void Shutter::shutter(unsigned long shutter_time_ms = DEFAULT_SHUTTER_WAIT) const
{
    digitalWrite(pin_shutter_, active_state_);
    delay(shutter_time_ms);
    digitalWrite(pin_shutter_, normal_state_);
}

void Shutter::afShutter(unsigned long af_time_ms = DEFAULT_AF_WAIT, unsigned long shutter_time_ms = DEFAULT_SHUTTER_WAIT) const
{
    digitalWrite(pin_shutter_, normal_state_);

    digitalWrite(pin_af_, active_state_);
    delay(af_time_ms);

    digitalWrite(pin_shutter_,active_state_);
    delay(shutter_time_ms);

    digitalWrite(pin_shutter_, normal_state_);
    digitalWrite(pin_af_, normal_state_);
}

}//namespace slider
#endif