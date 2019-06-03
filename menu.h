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
    Encoder* encoder;
    MenuItem* next;
    MenuItem* prev;
    MenuItem* up;
    virtual MenuItem* show() = 0;
    virtual MenuItem* action_right() = 0;
    virtual MenuItem* action_left() = 0;
    virtual MenuItem* action_press() = 0;
    virtual MenuItem* action_cancel() = 0;
    
};

#include "main_menu.h"// MAIN MENU


#endif menu_h