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

}//namespace slider
#endif //slider_display_h
