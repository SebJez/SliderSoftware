#ifndef menu_h
#define menu_h
#include <Encoder.h>
#include "lcd16x2.h"

class Menu
{
private:
    String* items;
    byte itemsNo;
    byte currentIndex = 0;
    uint8_t pinOK;
    uint8_t pinCancel;
    Encoder* encoder;
    Display* display;
public:
    Menu(String* items, uint8_t pinOK, uint8_t pinCancel, Encoder* encoder, Display* display):\
     items(items), pinOK(pinOK), pinCancel(pinCancel), encoder(encoder), display(display);

    byte run();
    
};

Menu::Menu(String* items, uint8_t pinOK, uint8_t pinCancel, Encoder* encoder, Display* display ):\
     items(items), pinOK(pinOK), pinCancel(pinCancel), encoder(encoder), display(display)
{
    pinMode(pinCancel, INPUT_PULLUP);
    pinMode(pinOK, INPUT_PULLUP);
    itemsNo = sizeof(items)/sizeof(items[0]);

}

byte Menu::run()
{
    currentIndex = 0;
    bool exitFlag = false;
    while(!exitFlag)
    {
        display->writeTopLine(">"+items[currentIndex]);
        if(currentIndex < itemsNo - 1) display->writeBottomLine(" "+items[currentIndex + 1]);

        int jump = encoder->read()/4;
        encoder->write(0);
        while (jump>0)
        {
            if(currentIndex > 0) currentIndex--;
            jump--;
        }
        while (jump<0)
        {
            if(currentIndex < itemsNo - 1) currentIndex ++;
            jump++;
        }
        if(digitalRead(pinCancel)==LOW) return 0xFF;
        if(digitalRead(pinOK)==LOW) return currentIndex;

    }
}
#endif
