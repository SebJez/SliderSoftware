#ifndef readKnob_h
#define readKnob_h

void readKnob(Encoder* knob, int pinOK, int pinCancel, void(*action_up)(), \
  void(*action_down)(), void(*action_press)(), void(*action_cancel)())
{
    byte knobPosition = knob->read()/4;
    while (knobPosition > 0)
    {
        action_up();
        knobPosition--;
    }
    while (knobPosition < 0)
    {
        action_down();
        knobPosition++;
    }
    knob->write(0);
    if(digitalRead(pinOK)==LOW) action_press();
    if(digitalRead(pinCancel)==LOW) action_cancel();

}

#endif
