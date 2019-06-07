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
        void writeBottomLeft(String text);
        void writeBottomMiddle(String text);
        void writeBottomRight(String text);
        Display(int pin_RS, int pin_E, int pin_D4, int pin_D5, int pin_D6, int pin_D7);
    private:
        String currentText[2];
        LiquidCrystal* lcd;
        void update();
    
    
};

Display::Display(int pin_RS, int pin_E, int pin_D4, int pin_D5, int pin_D6, int pin_D7)
{
    *lcd = LiquidCrystal(pin_RS,pin_E,pin_D4,pin_D5,pin_D6,pin_D7);
    lcd->begin(16,2);

    currentText[0].reserve(16);
    currentText[1].reserve(16);

    lcd->write("TEST");
}

void Display::update()
{
    lcd->clear();
    lcd->print(currentText[0]);
    lcd->setCursor(1,0);
    lcd->print(currentText[1]);
}

/*


Bottom line layout:

0123456789ABCDEF
LEFT|
     MIDDLE
           |RIGH
0123456789ABCDEF

*/
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

void Display::writeBottomLeft(String text)
{

    while(text.length() < 0x5) text += " ";
    text = text.substring(0x0,0x5);
    currentText[1]= text + currentText[1].substring(0x5);
    update();
}

void Display::writeBottomMiddle(String text)
{
    while(text.length() < 0x6) text += " ";
    text = text.substring(0x0,0x6);
    currentText[1]= currentText[1].substring(0x0,0x5) + text + currentText[1].substring(0xB);
    update();
}

void Display::writeBottomRight(String text)
{
   while(text.length() < 0x5) text += " ";
    text = text.substring(0x0,0x5);
    currentText[1]= currentText[1].substring(0x0,0xB)+text;
    update();
}

#endif //lcd16x2_h
