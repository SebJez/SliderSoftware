#ifndef motor_h
#define motor_h

#include <limits.h>

volatile bool motorStopFlag = false;
volatile bool endstopFlag = false;
    //improvement - use namespace for flags
class Motor
{
    long move(long steps, bool enable_endstops = true);
    float move(float distance_mm, bool enable_endstops = true);
    void setSpeed(float speed_mm_per_second);
    long getStep();
    float getPosition();
    Motor(int pinA1, int pinA2, int pinB1, int pinB2, int pinEndstop, int pinCancel, long steps_per_mm,\
     float speed_mm_per_second, bool flip_direction = false, long max_steps = LONG_MAX);
    long autoHome();
    long fullHome();

    private:
        void makeStep(bool clockwise);
        long stepNumber = 0;
        byte phase = 0; //overflow intended 
        unsigned long interval;
        unsigned long last_step_time = 0;
        long steps_per_mm;
        int pinA1;
        int pinA2;
        int pinB1;
        int pinB2;
        int pinEndstop;
        int pinCancel;
        bool enable_endstops;
        bool flip_direction;
        long max_steps;

};

Motor::Motor(int pinA1, int pinA2, int pinB1, int pinB2, int pinEndstop, int pinCancel, long steps_per_mm, \
  float speed_mm_per_second, bool flip_direction = false, long max_steps = LONG_MAX):\
  pinA1(pinA1),pinA2(pinA2),pinB1(pinB1),pinB2(pinB2),pinEndstop(pinEndstop),pinCancel(pinCancel), \
  steps_per_mm(steps_per_mm),flip_direction(flip_direction),enable_endstops(enable_endstops)
{
    pinMode(pinA1, OUTPUT);
    pinMode(pinA2, OUTPUT);
    pinMode(pinB1, OUTPUT);
    pinMode(pinB2, OUTPUT);
    pinMode(pinEndstop, INPUT_PULLUP);
    pinMode(pinCancel, INPUT_PULLUP);
    setSpeed(speed_mm_per_second);
}

void Motor::setSpeed(float speed_mm_per_second)
{
    interval = 1e6 / steps_per_mm / speed_mm_per_second;
}
void interruptEndstop()
{
    motorStopFlag = true;
    endstopFlag = true;
}

void interruptCancel()
{
    motorStopFlag = true;
}

long Motor::move(long steps, bool enable_endstops = true)
{
    attachInterrupt(digitalPinToInterrupt(pinEndstop),interruptEndstop, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinCancel),interruptCancel, FALLING);
    long steps_to_do = steps;
    
   if(enable_endstops)
   {
        long endpos = stepNumber+steps_to_do;
        if (endpos >= max_steps) steps_to_do = max_steps - stepNumber;
        else if (endpos < 0) steps_to_do = - stepNumber;
   }

    long remaining_steps = abs(steps_to_do);
    
    bool dir = (steps >= 0) ? 1 : 0;
    if(flip_direction) dir = !dir;

    while(remaining_steps>0 && motorStopFlag == false)
    {
        unsigned long now = micros();
        if(now - last_step_time >= interval)
        {
            if(dir)
            {
                switch (phase % 4)
                //--__--__
                //_--__--__
                //1001 1010 0110 0101
                //
                {
                case 0:
                    digitalWrite(pinA1, HIGH);
                    digitalWrite(pinA2, LOW);
                    digitalWrite(pinB1, LOW);
                    digitalWrite(pinB2, HIGH);
                    break;
                case 1:
                    digitalWrite(pinA1, HIGH);
                    digitalWrite(pinA2, LOW);
                    digitalWrite(pinB1, HIGH);
                    digitalWrite(pinB2, LOW);
                    break;
                case 2:
                    digitalWrite(pinA1, LOW);
                    digitalWrite(pinA2, HIGH);
                    digitalWrite(pinB1, HIGH);
                    digitalWrite(pinB2, LOW);
                    break;
                case 3:
                    digitalWrite(pinA1, LOW);
                    digitalWrite(pinA2, HIGH);
                    digitalWrite(pinB1, LOW);
                    digitalWrite(pinB2, HIGH);
                    break;
                }
                phase++;
                stepNumber++;
                
            }
            else
            {
                switch (phase % 4)
                {
                case 2:
                    digitalWrite(pinA1, HIGH);
                    digitalWrite(pinA2, LOW);
                    digitalWrite(pinB1, LOW);
                    digitalWrite(pinB2, HIGH);
                    break;
                case 3:
                    digitalWrite(pinA1, HIGH);
                    digitalWrite(pinA2, LOW);
                    digitalWrite(pinB1, HIGH);
                    digitalWrite(pinB2, LOW);
                    break;
                case 0:
                    digitalWrite(pinA1, LOW);
                    digitalWrite(pinA2, HIGH);
                    digitalWrite(pinB1, HIGH);
                    digitalWrite(pinB2, LOW);
                    break;
                case 1:
                    digitalWrite(pinA1, LOW);
                    digitalWrite(pinA2, HIGH);
                    digitalWrite(pinB1, LOW);
                    digitalWrite(pinB2, HIGH);
                    break;
                }
                phase--;
                stepNumber--;
                
            }
            remaining_steps--;
            last_step_time = now;
        }
    }
    motorStopFlag = false;
    detachInterrupt(digitalPinToInterrupt(pinEndstop));
    detachInterrupt(digitalPinToInterrupt(pinCancel));
    return stepNumber;
}

float Motor::move(float distance_mm, bool enable_endstops)
{
    long steps = distance_mm * steps_per_mm;
    return ((float)move(steps),enable_endstops)/((float)steps_per_mm);
}

long Motor::getStep()
{
    return stepNumber;
}

float Motor::getPosition()
{
    return (float)stepNumber/steps_per_mm;
}


long Motor::autoHome()
{
    move(-LONG_MIN,false);
    if(endstopFlag)
    {
        stepNumber = 0;
        endstopFlag = false;
    }
    return stepNumber;
}

long Motor::fullHome()
{
    autoHome();
    move(LONG_MAX,false);
    if (endstopFlag)
    {
        max_steps = stepNumber;
        endstopFlag = false;
    }
    return stepNumber;
}
#endif //motor_h
