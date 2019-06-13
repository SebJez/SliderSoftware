#ifndef setValue_h
#define setValue_h
#include <Encoder.h>
#include "lcd16x2.h"
#include "sparkleUtils.h"

typedef uint8_t pin;

class SetValue
{
private:
    String textTop;
    String unit;
    pin pinOk;
    pin pinCancel;
    Display* display;
    Encoder* encoder;
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
        pin pinOk, pin pinCancel, Display* display, Encoder* encoder, String unit="", byte digitsAfterDecimal = 0,\
        String minValueText="", String maxValueText="");
    ~SetValue();
    byte run(); //returns exit code 0 - user cancelled
                //        exit code 1 - value set
    long getValue() {return value;};
    void setValue(long defaultVal){defaultValue = defaultVal;};
    void updateDisplay();
    //String formatValue(long value);
};

SetValue::SetValue(String textTop, long minValue, long maxValue, long defaultValue, long step,\
        pin pinOk, pin pinCancel, Display* display, Encoder* encoder, String unit="", byte digitsAfterDecimal = 0,\
        String minValueText="", String maxValueText=""):textTop(textTop), minValue(minValue),maxValue(maxValue), defaultValue(defaultValue),step(step),\
        pinOk(pinOk), pinCancel(pinCancel), display(display), encoder(encoder), unit(unit), digitsAfterDecimal(digitsAfterDecimal),\
        minValueText(minValueText), maxValueText(maxValueText)
{
    value = defaultValue;
    pinMode(pinOk, INPUT_PULLUP);
    pinMode(pinCancel, INPUT_PULLUP);
    encoder->write(0);

}

SetValue::~SetValue()
{
}

byte SetValue::run()
{
    value = defaultValue;
    bool displayChanged = true;
    encoder->write(0);
 
    while (true)
    {
        if(displayChanged) updateDisplay();
        displayChanged = false;
        long newValue = value;
        int encoderpos = encoder->read();

        if(encoderpos > 3 || encoderpos < -3)
        {
            newValue = (encoderpos/4)*step+value;
            delay(100);
            encoder->write(0);
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

    if(value >= maxValue && maxValueText != "") bottomText = maxValueText;
    else if(value <= minValue && minValueText != "") bottomText = minValueText;
    else bottomText = sparkle::formatInteger<long>(value,digitsAfterDecimal, postfix=unit);

    bottomText = sparkle::padString(bottomText,0x10);
    display->writeBottomLine(bottomText);
}

#endif
