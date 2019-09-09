#ifndef slider_list_cpp
#define slider_list_cpp
#include "slider_list.h"
namespace slider
{

ListMenu::ListMenu(const unsigned char no_of_elements, String* elements, \
                RotaryEncoder* encoder, Pin cancel_pin, Pin ok_pin, Display* display):
                no_of_elements_(no_of_elements < 0xff ? no_of_elements : 0xfe),
                elements_(elements),
                encoder_(encoder),
                cancel_pin_(cancel_pin),
                ok_pin_(ok_pin),
                display_(display)
{
    pinMode(cancel_pin_, INPUT_PULLUP);
    pinMode(ok_pin_, INPUT_PULLUP);
}

unsigned char ListMenu::run(unsigned char start_position = 0) const
{
    position_ = start_position;
    if (position_ >= no_of_elements_) position_ = no_of_elements_ -1;
    bool update_display_flag = true;
   
    while (true)
    {
        if(update_display_flag)
        {
            updateDisplay();
            update_display_flag = false;
        }
        encoder_->setPosition(0);
        encoder_->tick();

        unsigned char move = encoder_->getPosition();
        while (move < 0 && position_ >= 0)
        {
            update_display_flag = true;
            --position_;
            ++move;
        }

        while (move > 0 && position_ < no_of_elements_)
        {
            update_display_flag = true;
            ++position_;
            --move;
        }        

        if (digitalRead(ok_pin_) == LOW) return position_;
        if (digitalRead(cancel_pin_) == LOW) return 0xFF;
    }
    
    
}

void ListMenu::updateDisplay()
{
 display_->writeTopLine(">"+elements[position_]);
    
    if (position + 1 < no_of_elements_)
        display_->writeBottomLine(" "+elements[position_]);
    else
        display_->writeBottomLine("");
    
}


} // namespace slider


#endif
