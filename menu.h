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
    Menu(String* items, uint8_t pinOK, uint8_t pinCancel, Encoder* encoder, Display* display);

    byte run();
    
};

Menu::Menu(String* items, uint8_t pinOK, uint8_t pinCancel, Encoder* encoder, Display* display ):\
     items(items), pinOK(pinOK), pinCancel(pinCancel), encoder(encoder), display(display)
{
    pinMode(pinCancel, INPUT_PULLUP);
    pinMode(pinOK, INPUT_PULLUP);
    itemsNo = sizeof(items)/sizeof(items[0]); //DOESN'T WORK
    itemsNo = 3;

}

byte Menu::run()
{
    currentIndex = 0;
    bool screenChanged = true;
    while(true)
    {
        if(screenChanged)
        {
          display->writeTopLine(">"+items[currentIndex]);
          if(currentIndex < itemsNo - 1) display->writeBottomLine(" "+items[currentIndex + 1]);
          else display->writeBottomLine("");
          screenChanged = false;
        }
        //delay(1000);
        int encoder_position = encoder->read();
        int jump = 0;
        if(encoder_position > 3 || encoder_position < -3)
        {
          jump = encoder_position/4;
          delay(50);
          encoder->write(0);
        }
        while (jump>0)
        {
            screenChanged = true;
            if(currentIndex > 0) currentIndex--;
            jump--;
        }
        while (jump<0)
        {
            screenChanged = true;
            if(currentIndex < itemsNo - 1) currentIndex ++;
            jump++;
        }
        //delay(100);
        if(digitalRead(pinCancel)==LOW) return 0xFF;
        if(digitalRead(pinOK)==LOW) return currentIndex;

    }
}
#endif
