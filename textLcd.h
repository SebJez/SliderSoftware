#ifndef textLcd_h
#define textLcd_h
#include <LiquidCrystal.h>
//#include <assert.h>

/*


Bottom line layout:

0123456789ABCDEF
LEFT|
     MIDDLE
           |RIGH
0123456789ABCDEF

*/

class TextLCD
{
    public:
        void writeLine(byte line, String text);
        //void writeBottomLine(String text);
        TextLCD(byte width, byte height, int pin_E, int pin_RS, int pin_D4, int pin_D5, int pin_D6, int pin_D7);
        ~TextLCD();
        String padRight(String);
    private:
        String* currentText;
        LiquidCrystal* lcd;
        void update();
        byte width;
        byte height;
    
    
};

TextLCD::TextLCD(byte width, byte height, int pin_RS, int pin_E, int pin_D4, int pin_D5, int pin_D6, int pin_D7)
{
    lcd = new LiquidCrystal(pin_RS,pin_E,pin_D4,pin_D5,pin_D6,pin_D7);
    lcd->begin(width,height);
    for(byte i=0; i<height; i++)
        currentText[i].reserve(width);
}
TextLCD::~TextLCD()
{
  delete(lcd);
}

void TextLCD::update()
{
    lcd->clear();
    for(byte i=0; i<height; i++)
    {
        lcd->setCursor(0,i);
        lcd->print(currentText[i]);
    }

}

/*


Bottom line layout:

0123456789ABCDEF
LEFT|
     MIDDLE
           |RIGH
0123456789ABCDEF

*/
void TextLCD::writeLine(byte line, String text)
{
    while(text.length() < width-1) text += " ";
    text = text.substring(0,width);
    currentText[line]=text;
    update();
}

/*
void Display::writeBottomLine(String text)
{
    while(text.length() < 0xF) text += " ";
    text = text.substring(0x0,0x10);
    currentText[1]=text;
    update();
}
*///refactor

String TextLCD::padRight(String text)
{
    while(text.length() < width) text = " "+text;
    return text;
}
#endif //textLcd_h
