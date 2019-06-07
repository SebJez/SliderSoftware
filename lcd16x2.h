#ifndef lcd16x2_h
#define lcd16x2_h
#include <LiquidCrystal.h>

/*
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
        String getTopLine();
        String getBottomLine();
        Display(int pin_E, int pin_RS, int pin_D4, int pin_D5, int pin_D6, int pin_D7);
        void update();
    private:
        String currentText[2];
        LiquidCrystal* lcd;
        
    
    
};

Display::Display(int pin_RS, int pin_E, int pin_D4, int pin_D5, int pin_D6, int pin_D7)
{
    *lcd = LiquidCrystal(pin_RS,pin_E,pin_D4,pin_D5,pin_D6,pin_D7);
    lcd->begin(16,2);

    currentText[0].reserve(16);
    currentText[1].reserve(16);
}

void Display::update()
{
    lcd->clear();
    lcd->print(currentText[0]);
    lcd->setCursor(1,0);
    lcd->print(currentText[1]);
}

void Display::writeTopLine(String text)
{
    while(text.length() < 0xF) text += " ";
    text = text.substring(0x0,0xF);
    currentText[0]=text;
    update();
}

void Display::writeBottomLine(String text)
{
    while(text.length() < 0xF) text += " ";
    text = text.substring(0x0,0xF);
    currentText[1]=text;
    update();
}

String Display::getTopLine()
{
    return currentText[0];
}

String Display::getBottomLine()
{
    return currentText[1];
}

#endif //lcd16x2_h
