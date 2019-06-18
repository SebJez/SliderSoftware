#ifndef slider_display_h
#define slider_display_h
#include <LiquidCrystal.h>

namespace slider
{

typedef const uint8_t Pin;

class Display
{
    public:
        void writeTopLine(String text);
        void writeBottomLine(String text);
        Display(Pin pin_E, Pin pin_RS, Pin pin_D4, Pin pin_D5, Pin pin_D6, Pin pin_D7);
        ~Display();
        String padRight(String text) const;
        String pad(String text,byte split_position) const;

    private:
        String currentText[2];
        LiquidCrystal* lcd;
        void update();
    
    
};

template<class integer_t> 
    String formatInteger(integer_t value,byte decimal_places = 0, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "");

template<class float_t>
    String formatFloatingPoint(float_t value, byte decimal_places, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "");



}//namespace slider
#endif //slider_display_h
