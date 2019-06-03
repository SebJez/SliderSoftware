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


//MAIN MENU

class MainMenu : MenuItem
{
public:

    MainMenu(Display display): lcd(display)
    {   
        next = this;
        prev = this;
        up = this;
        name = T_MAIN_MENU;
    }

    MenuItem* item = nullptr; //pointer to first item 

    MenuItem* show()
    {
        lcd->writeTopLine(">" + item->name);
        lcd->writeBottomLine(" " + item->next->name);
        lcd->update();
        return this;
    }

    MenuItem* action_right()
    {
        item = item->next;
        show();
        return this;
    }

    MenuItem* action_left()
    {
        item = item->prev;
        show();
        return this;
    }

    MenuItem* action_press()
    {
        return item->show();
    }
    MenuItem* action_cancel();
    {
        return up->show();
    }
};



#endif menu_h