#ifndef slider_display_cpp
#define slider_display_cpp
#include <LiquidCrystal.h>
#include "slider_display.h"


namespace slider
{

Display::Display(Pin pin_RS, Pin pin_E, Pin pin_D4, Pin pin_D5, Pin pin_D6, Pin pin_D7)
{
    lcd = new LiquidCrystal(pin_RS,pin_E,pin_D4,pin_D5,pin_D6,pin_D7);
    lcd->begin(16,2);

    currentText[0].reserve(16);
    currentText[1].reserve(16);
}
Display::~Display()
{
  delete(lcd);
}

void Display::update()
{
    lcd->clear();
    lcd->print(currentText[0]);
    lcd->setCursor(0,1);
    lcd->print(currentText[1]);
}

void Display::writeTopLine(String text)
{
    while(text.length() < 0xF) text += " ";
    text = text.substring(0x0,0x10);
    currentText[0]=text;
    update();
}

void Display::writeBottomLine(String text)
{
    while(text.length() < 0xF) text += " ";
    text = text.substring(0x0,0x10);
    currentText[1]=text;
    update();
}

String Display::padRight(String text)
{
    while(text.length()<0x10) text = " "+text;
    return text;
}

String Display::pad(String text, byte split_position)
{
    while(text.length()<0x10) text = text.substring(0,split_position)+" "+text.substring(split_position);
    return text;
}

String formatInteger(integer_t value,byte decimal_places = 0, bool use_plus_sign = false,\
                                     String prefix = "", String postfix = "")
{
    String number = String(abs(value));

    while(number.length() <= decimal_places) number = "0" + number;
    
    if(use_plus_sign)
        String sign = (value < 0) ? "-" : "+";
    else
        String sign = (value < 0) ? "-" : "";

    String separator = (decimal_places > 0) ? "." : "";

    byte len = number.length();

    return prefix + sign + number.substring(0,len-decimal_places) + \
            separator + number.substring(len-decimal_places,len) + postfix;
    
}

String formatFloatingPoint(float_t value, byte decimal_places, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "")
{
    String number = String(value,decimal_places);
    if (use_plus_sign && value >= 0) number = "+" + number;

    return prefix + number + postfix;
}

}
#endif //slider_display_h
