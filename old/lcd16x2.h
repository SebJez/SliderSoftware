#ifndef lcd16x2_h
#define lcd16x2_h
#include <LiquidCrystal.h>
#include <assert.h>

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
        Display(int pin_E, int pin_RS, int pin_D4, int pin_D5, int pin_D6, int pin_D7);
        ~Display();
        String padRight(String);
    private:
        String currentText[2];
        LiquidCrystal* lcd;
        void update();
    
    
};

Display::Display(int pin_RS, int pin_E, int pin_D4, int pin_D5, int pin_D6, int pin_D7)
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
#endif //lcd16x2_h
