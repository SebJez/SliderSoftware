#ifndef slider_shutter_h
#define slider_shutter_h

#include "config.h"

namespace slider
{

typedef const unsigned char Pin;

class Shutter
{
private:
    Pin pin_shutter_;
    Pin pin_af_;
    unsigned char normal_state_;
    unsigned char active_state_;
public:
    Shutter(Pin pin_shutter, Pin pin_af);
    void af(unsigned long af_time_ms = DEFAULT_AF_WAIT) const;
    void shutter(unsigned long shutter_time_ms = DEFAULT_SHUTTER_WAIT) const;
    void afShutter(unsigned long af_time_ms = DEFAULT_AF_WAIT, unsigned long shutter_time_ms = DEFAULT_SHUTTER_WAIT) const;
    
};


}//namespace slider
#endif //slider_shutter_h