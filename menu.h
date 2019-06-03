#ifndef menu_h
#define menu_h
#include "lcd16x2.h"
class MenuItem
{
private:
    /* data */
public:
    String name;
    Display* lcd;
    MenuItem* next;
    MenuItem* prev;
    MenuItem* up;
    virtual MenuItem* show() = 0;
    virtual MenuItem* action_right() = 0;
    virtual MenuItem* action_left() = 0;
    virtual MenuItem* action_press() = 0;
    virtual MenuItem* action_cancel() = 0;
    
};

class SubMenu : MenuItem
{
    public:
    Element(Display* lcd, MenuItem* next, MenuItem* prev, MenuItem* up) :\
    lcd(lcd),next(next),prev(prev),up(up) {}
};

#include "main_menu.h"// MAIN MENU
#include "manual_control.h"// MANUAL CONTROL

#endif menu_h