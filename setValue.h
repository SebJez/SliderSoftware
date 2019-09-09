#ifndef setValue_h
#define setValue_h
#include <RotaryEncoder.h>
#include "lcd16x2.h"

typedef uint8_t pin;

class SetValue
{
private:
    String textTop;
    String unit;
    pin pinOk;
    pin pinCancel;
    Display* display;
    RotaryEncoder* encoder;
    byte digitsAfterDecimal;

    long minValue;
    String minValueText;
    long maxValue;
    String maxValueText;

    long defaultValue;
    long step; 
    long value;
public:
    SetValue(String textTop, long minValue, long maxValue, long defaultValue, long step,\
        pin pinOk, pin pinCancel, Display* display, RotaryEncoder* encoder, String unit="", byte digitsAfterDecimal = 0,\
        String minValueText="", String maxValueText="");
    ~SetValue();
    byte run(); //returns exit code 0 - user cancelled
                //        exit code 1 - value set
    long getValue() {return value;};
    void setValue(long defaultVal){defaultValue = defaultVal;};
    void updateDisplay();
};

SetValue::SetValue(String textTop, long minValue, long maxValue, long defaultValue, long step,\
        pin pinOk, pin pinCancel, Display* display, RotaryEncoder* encoder, String unit="", byte digitsAfterDecimal = 0,\
        String minValueText="", String maxValueText=""):textTop(textTop), minValue(minValue),maxValue(maxValue), defaultValue(defaultValue),step(step),\
        pinOk(pinOk), pinCancel(pinCancel), display(display), encoder(encoder), unit(unit), digitsAfterDecimal(digitsAfterDecimal),\
        minValueText(minValueText), maxValueText(maxValueText)
{
    value = defaultValue;
    pinMode(pinOk, INPUT_PULLUP);
    pinMode(pinCancel, INPUT_PULLUP);
    encoder->setPosition(0);

}

SetValue::~SetValue()
{
}

byte SetValue::run()
{
    value = defaultValue;
    bool displayChanged = true;
    encoder->setPosition(0);
 
    while (true)
    {
        if(displayChanged) updateDisplay();
        displayChanged = false;
        long newValue = value;
        int encoderpos = encoder->getPosition();

        if(encoderpos != 0)
        {
            newValue = encoderpos*step+value;
            delay(100);
            encoder->setPosition(0);
        }
        if (value != newValue)
        {
            if(newValue < minValue) value = minValue;
            else if(newValue > maxValue) value = maxValue;
            else value = newValue;
            displayChanged = true;
        }
        
        if(digitalRead(pinOk)==LOW) return 0x01;
        if(digitalRead(pinCancel)==LOW) return 0x00;
    }
    
}

void SetValue::updateDisplay()
{
    display->writeTopLine(textTop);
    String bottomText = String(abs(value));
    
    while(bottomText.length()<=digitsAfterDecimal) bottomText = "0" + bottomText;
    if(value < 0) bottomText = "-"+bottomText;

    if(value >= maxValue && maxValueText != "") bottomText = maxValueText;
    else if(value <= minValue && minValueText != "") bottomText = minValueText;
    else
    {
        byte length = bottomText.length();
        if(digitsAfterDecimal > 0)
        {
            bottomText = bottomText.substring(0,length-digitsAfterDecimal)+\
                        "."+bottomText.substring(length-digitsAfterDecimal);
        }
        bottomText = bottomText + unit;
    }

    bottomText = display->padRight(bottomText);
    display->writeBottomLine(bottomText);
}


#endif
