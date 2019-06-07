#ifndef menu_h
#define menu_h

#include "lcd16x2.h"
#include <Encoder.h>
#include "readKnob.h"

typedef struct s_menuItem {String subprogram_name; void(*subprogram)();} MenuItem;

class Menu
{
    public:
        unsigned int current_item = 0;
    private:
        Encoder* knob;
        Display* lcd;
        int pinOK;
        int pinCancel;
        MenuItem* items;
        unsigned int menuLenght;
        bool exitFlag = false;
        void run(unsigned int start_from_item=0);

    public:

    Menu(Display* lcd, Encoder* knob, int pinOK, int pinCancel, MenuItem* items,\
      unsigned int start_from_item = 0): lcd(lcd),knob(knob), pinOK(pinOK), \
      pinCancel(pinCancel),items(items)
    {
        pinMode(pinOK, INPUT_PULLUP);
        pinMode(pinCancel, INPUT_PULLUP);
        menuLenght = sizeof(items)/sizeof(items[0]);
    }
};

void Menu::menuUp()
{
    if(current_item < menuLenght - 1)
    {
        current_item++;
        lcd->writeTopLine(">"+items[current_item].subprogram_name);

      if(current_item < menuLenght - 1)
        lcd->writeBottomLine(" "+items[current_item+1].subprogram_name);
      else
        lcd.writeBottomLine(" ");  
    }
}

void Menu::menuDown()
{
    if(current_item > 0)
    {
      current_item--;
      lcd->writeTopLine(">"+items[current_item].subprogram_name);

      if(current_item < menuLenght - 1)
        lcd->writeBottomLine(" "+items[current_item+1].subprogram_name);
      else
        lcd->writeBottomLine(" ");

    }
}

void Menu::menuOK()
{
    items[current_item].subprogram();
}

void Menu::menuCancel()
{
    exitFlag = true;
}

void Menu::run(unsigned int start_from_item)
{
    current_item = start_from_item;

    lcd->writeTopLine(">"+items[current_item].subprogram_name);

    if(current_item < menuLenght - 1)
        lcd->writeBottomLine(" "+items[current_item+1].subprogram_name);
    else
        lcd->writeBottomLine(" ");
    
    while(!exitFlag)
        readKnob(knob, pinOK, pinCancel, &menuUp, &menuDown, &menuOK, &menuCancel);
}

#endif //menu_h
