#ifndef main_menu_h
#define main_menu_h
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

#endif //main_menu_h