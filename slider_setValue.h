#ifndef slider_set_value_h
#define slider_set_value_h
#include "slider_display.h"
#include <RotaryEncoder.h>

namespace slider
{
typedef const unsigned char Pin;

bool setValuePrompt(long* value, Display* display, RotaryEncoder* encoder,Pin ok_pin, Pin cancel_pin ,String text, \
                long min_val, long max_val, long def_val = min_val, long step = 1L,\
                unsigned char decimal_places = 0, bool use_plus_sign = false,String prefix = "", String postfix = "")
//returns true if value was changed, false if user cancelled
{
    display->writeTopLine(text);
    long current_val = def_val;
    display->writeBottomLine(display->padRight(formatInteger(current_val,decimal_places,use_plus_sign,prefix,postfix)));
    while (true)
    {
        encoder->setPosition(0);
        encoder->tick();
        long new_val = current_val + encoder->getPosition()*step;
        if(new_val > max_val) new_val = max_val;
        if(new_val < min_val) new_val = min_val;
        if(new_val != current_val)
        {
            current_val = new_val;
            display->writeBottomLine(display->padRight(formatInteger(current_val,decimal_places,use_plus_sign,prefix,postfix)));
        }

        if(digitalRead(ok_pin)==LOW)
        {
            *value = current_val;
            return true;
        }
        if(digitalRead(cancel_pin)==LOW)
        {
            return false;
        }
    }
}

}//namespace slider

#endif
