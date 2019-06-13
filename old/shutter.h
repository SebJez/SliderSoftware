#ifndef remote_shutter_h
#define remote_shutter_h

class Shutter
{
private:
    int pin_shutter;
    int pin_af;
    bool use_af;
    bool invert;
    byte active;
    byte normal;
public:
    Shutter(int pin_shutter, int pin_af, bool invert = false);
    Shutter(int pin_shutter, bool invert = false);
    void af(unsigned long af_time_ms = 100);
    void shutter(unsigned long shutter_time_ms = 100);
    void afShutter(unsigned long af_time_ms = 100, shutter_time_ms = 100);
    
};

Shutter::Shutter(int pin_shutter, int pin_af, bool invert = false): \
  pin_shutter(pin_shutter), pin_af(pin_af), invert(invert)
{
    use_af = true;
    active = invert ? LOW : HIGH;
    normal = invert ? HIGH : LOW;
    pinMode(pin_shutter, OUTPUT);
    digitalWrite(pin_shutter, normal);
    pinMode(pin_af, OUTPUT);
    digitalWrite(pin_af, normal);

}
Shutter::Shutter(int pin_shutter, bool invert = false): \
  pin_shutter(pin_shutter), invert(invert)
{
    use_af = false;
    pin_af = -1;
    active = invert ? LOW : HIGH;
    normal = invert ? HIGH : LOW;
    pinMode(pin_shutter, OUTPUT);
    digitalWrite(pin_shutter, normal);

}

void Shutter::af(unsigned long af_time_ms)
{
    if(use_af)
    {
        digitalWrite(pin_af, active);
        delay(af_time_ms);
        digitalWrite(pin_af, normal);
    }
}

void Shutter::shutter(unsigned long shutter_time_ms)
{
    digitalWrite(pin_shutter, active);
    delay(shutter_time_ms);
    digitalWrite(pin_shutter, normal);
}

void Shutter::afShutter(unsigned long af_time_ms, unsigned long shutter_time_ms)
{
    digitalWrite(pin_shutter, normal);
    if(use_af)
    {
        digitalWrite(pin_af, active);
        delay(af_time_ms);
    }
    digitalWrite(pin_shutter,active);
    delay(shutter_time_ms);
    digitalWrite(pin_shutter, normal);
    if(use_af) digitalWrite(pin_af, normal);
}
#endif //remote_shutter_h
