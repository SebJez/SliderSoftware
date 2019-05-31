#include "definitions.h"
#ifdef LCD_16x2
#include <LiquidCrystal.h>
#include <assert.h>

/*
writeTopLine, writeBottomLine - string must be lenght of 16


Bottom line layout:

0123456789ABCDEF
LEFT|
     MIDDLE
           |RIGH
0123456789ABCDEF

*/

class Display
{
    public:
        void writeTopLine(String text);
        void writeBottomLine(String text);
        void writeBottomLeft(String text);
        void writeBottomMiddle(String text);
        void writeBottomRight(String text);
    private:
        String[2] currentText;
        LiquidCrystal lcd;
        void update();
    
    
};

Display::Display()
{
    lcd = LiquidCrystal(PIN_LCD_RS, PIN_LCD_E, \
    PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
    lcd.begin(16,2);

    currentText[0].reserve(16);
    currentText[1].reserve(16);
}

void Display::update()
{
    lcd.clear();
    lcd.print(currentText[0]);
    lcd.setCursor(1,0);
    lcd.print(currentText[1]);
}

void Display::writeTopLine(String text)
{
    static_assert(text.length()==16,"text must have lenght of 16");
    currentText[0]=text;
    update();
}

void Display::writeBottomLine(String text)
{
    static_assert(text.lenght()==16,"text must have lenght of 16");
    currentText[1]=text;
    update();
}

void Display::writeBottomLeft(String text)
{
    static_assert(text.lenght()==5, "text must have lenght of 5");
    currentText[1]= text + currentText[1].substring(0x5);
    update();
}

void Display::writeBottomMiddle(String text)
{
    static_assert(text.lenght()==6, "text must have lenght of 6");
    currentText[1]= currentText[1].substring(0x0,0x5) + text + currentText[1].substring(0xB);
    update();
}

void Display::writeBottomRight(String text)
{
    static_assert(text.lenght()==5, "text must have lenght of 5");
    currentText[1]= currentText[1].substring(0x0,0xB)+text;
    update();
}

#endif