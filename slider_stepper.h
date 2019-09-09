#ifndef slider_stepper_h
#define slider_stepper_h

namespace slider
{

typedef const unsigned char Pin;

enum StepperFlag : unsigned char
{
    OK_FLAG = 0x00,
    CANCEL_FLAG = 0x01,
    ENDSTOP_FLAG = 0x02
};

void onEndstop()
{
    //flag = ENDSTOP_FLAG;
}

void onCancel()
{
    //flag = CANCEL_FLAG;
}

class LiveStepper;

class Stepper
{
    friend class LiveStepper;
    public:
        Stepper(Pin pin_A1,Pin pin_A2,Pin pin_B1,Pin pin_B2, Pin pin_endstop, Pin pin_cancel,\
                    float steps_per_mm,float speed_mm_per_s,long max_step);
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
        inline StepperFlag getFlag() const;
        inline float stepsToMm(long steps) const;
        inline long mmToSteps(float milimetres) const;
     

    protected:
        void stepForward();
        void stepBack();
        inline void setState(const unsigned char state);
        long current_step_;
        int8_t current_phase_;
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

} //namespace slider

#endif
