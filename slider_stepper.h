#ifndef slider_stepper_h
#define slider_stepper_h

namespace slider
{

typedef const uint8_t Pin;

enum StepperFlag : byte
{
    OK_FLAG = 0x00,
    CANCEL_FLAG = 0x01,
    ENDSTOP_FLAG = 0x02
};

void onEndstop()
{
    flag = ENDSTOP_FLAG;
}

void onCancel()
{
    flag = CANCEL_FLAG;
}

class Stepper
{
    public:
        Stepper(Pin pin_A1,Pin pin_A2,Pin pin_B1,Pin pin_B2, Pin pin_endstop, Pin pin_cancel,\
                    float steps_per_mm,float speed_mm_per_s,long max_step,bool using_tick = false, CallbackFunction tick = nullptr)
        inline long getStep() const;
        inline float getPosition() const;
        inline long moveTo(long position_steps, bool software_endstops=true);
        inline float moveTo(float position_mm, bool software_endstops=true);
        long moveBy(long steps, bool software_endstops=true);
        inline float moveBy(float milimetres, bool software_endstops=true);
        long home();
        long homeOnMax();
        inline float setSpeed(float milimetres_per_second);
        inline float getSpeed() const;

    protected:
        inline void setState(const byte state);
        virtual void tick()=0;
        long current_step_;
        byte current_phase_;
        long max_step_;
        float steps_per_mm_;
        unsigned int interval_ms_;
        Pin pin_A1_;
        Pin pin_A2_;
        Pin pin_B1_;
        Pin pin_B2_;
        Pin pin_endstop_;
        Pin pin_cancel_;
        StepperFlag flag_;

};

class StepperNoTick : public Stepper
{
    inline void tick(){} 
};

} //namespace slider

#endif