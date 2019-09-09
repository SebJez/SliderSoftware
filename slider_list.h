#ifndef slider_list_h
#define slider_list_h
#include "slider_display.h"
#include <RotaryEncoder.h>
namespace slider
{
typedef const unsigned char Pin;

class ListMenu
{
    public:
        ListMenu(const unsigned char no_of_elements, String* elements, RotaryEncoder* encoder,\
                     Pin cancel_pin, Pin ok_pin, Display* display);
        unsigned char run(unsigned char start_position = 0) const
    protected:
        const String* elements_;
        const unsigned char no_of_elements_;
        unsigned char position_;
        Pin cancel_pin_;
        Pin ok_pin_;
        const RotaryEncoder* encoder_;
        const Display* display_;
        void updateDisplay();
};
} // namespace slider
#endif
