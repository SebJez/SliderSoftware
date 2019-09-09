#ifndef menu_h
#define menu_h
#include <RotaryEncoder.h>
#include "lcd16x2.h"

class Menu
{
private:
    String* items;
    byte numberOfItems;
    byte currentIndex = 0;
    uint8_t pinOK;
    uint8_t pinCancel;
    RotaryEncoder* encoder;
    Display* display;
public:
    Menu(String* items, byte numberOfItems, uint8_t pinOK, uint8_t pinCancel, RotaryEncoder* encoder, Display* display);

    byte run();
    
};

Menu::Menu(String* items, byte numberOfItems, uint8_t pinOK, uint8_t pinCancel, RotaryEncoder* encoder, Display* display ):\
     items(items), numberOfItems(numberOfItems), pinOK(pinOK), pinCancel(pinCancel), encoder(encoder), display(display)
{
    pinMode(pinCancel, INPUT_PULLUP);
    pinMode(pinOK, INPUT_PULLUP);

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
          if(currentIndex < numberOfItems - 1) display->writeBottomLine(" "+items[currentIndex + 1]);
          else display->writeBottomLine("");
          screenChanged = false;
        }
        
        int encoder_position = encoder->getPosition();
        int jump = 0;

        
        if(encoder_position != 0)
        {
          jump = encoder_position;
          delay(100);
          encoder->setPosition(0);
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
            if(currentIndex < numberOfItems - 1) currentIndex ++;
            jump++;
        }
        
        if(digitalRead(pinCancel)==LOW) return 0xFF;
        if(digitalRead(pinOK)==LOW) return currentIndex;

    }
}
#endif
