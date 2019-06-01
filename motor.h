#ifndef motor_h
#define motor_h
#include "definitions.h"

class Motor
{
    long move(long steps);
    float move(float distance_mm);
    float setSpeed(float speed_mm_per_second);
    long getStep();
    float getPosition();

    private:
        void makeStep(bool clockwise);
        long stepNumber = 0;
        byte phase = 0;
        bool stop_flag = false;
        unsigned long interval = 1000000L/STEPS_PER_MM/DEFAULT_SPEED;
        unsigned long last_step_time = 0;

};

void Motor::setSpeed(float speed_mm_per_second)
{
    interval = 1000000L / STEPS_PER_MM / speed_mm_per_second;
}

long Motor::move(long steps)
{
    long steps_to_do = steps;
    
    #ifdef SOFTWARE_ENDSTOPS
        long endpos = stepNumber+steps_to_do;
        if (endpos >= MAX_STEPS) steps_to_do = MAX_STEPS - stepNumber;
        else if (endpos < 0) steps_to_do = - stepNumber;
    #endif

    long remaining_steps = abs(steps_to_do);
    
    #ifdef FLIP_DIRECTION
    bool dir =   distance>=0 ? 1 : 0;
    #else
    bool dir =   distance>=0 ? 0 : 1;
    #endif

    while(remaining_steps>0 && stop_flag == false)
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
                    digitalWrite(PIN_STEPPER_A1, HIGH);
                    digitalWrite(PIN_STEPPER_A2, LOW);
                    digitalWrite(PIN_STEPPER_B1, LOW);
                    digitalWrite(PIN_STEPPER_B2, HIGH);
                    break;
                case 1:
                    digitalWrite(PIN_STEPPER_A1, HIGH);
                    digitalWrite(PIN_STEPPER_A2, LOW);
                    digitalWrite(PIN_STEPPER_B1, HIGH);
                    digitalWrite(PIN_STEPPER_B2, LOW);
                    break;
                case 2:
                    digitalWrite(PIN_STEPPER_A1, LOW);
                    digitalWrite(PIN_STEPPER_A2, HIGH);
                    digitalWrite(PIN_STEPPER_B1, HIGH);
                    digitalWrite(PIN_STEPPER_B2, LOW);
                    break;
                case 3:
                    digitalWrite(PIN_STEPPER_A1, LOW);
                    digitalWrite(PIN_STEPPER_A2, HIGH);
                    digitalWrite(PIN_STEPPER_B1, LOW);
                    digitalWrite(PIN_STEPPER_B2, HIGH);
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
                    digitalWrite(PIN_STEPPER_A1, HIGH);
                    digitalWrite(PIN_STEPPER_A2, LOW);
                    digitalWrite(PIN_STEPPER_B1, LOW);
                    digitalWrite(PIN_STEPPER_B2, HIGH);
                    break;
                case 3:
                    digitalWrite(PIN_STEPPER_A1, HIGH);
                    digitalWrite(PIN_STEPPER_A2, LOW);
                    digitalWrite(PIN_STEPPER_B1, HIGH);
                    digitalWrite(PIN_STEPPER_B2, LOW);
                    break;
                case 0:
                    digitalWrite(PIN_STEPPER_A1, LOW);
                    digitalWrite(PIN_STEPPER_A2, HIGH);
                    digitalWrite(PIN_STEPPER_B1, HIGH);
                    digitalWrite(PIN_STEPPER_B2, LOW);
                    break;
                case 1:
                    digitalWrite(PIN_STEPPER_A1, LOW);
                    digitalWrite(PIN_STEPPER_A2, HIGH);
                    digitalWrite(PIN_STEPPER_B1, LOW);
                    digitalWrite(PIN_STEPPER_B2, HIGH);
                    break;
                }
                phase--;
                stepNumber--;
                
            }
            remaining_steps--;
            last_step_time = now;
        }
    }
    return stepNumber;
}

float Motor::move(float distance_mm)
{
    long steps = distance_mm * STEPS_PER_MM;
    return ((float)move(steps))/((float)STEPS_PER_MM);
}

long Motor::getStep()
{
    return stepNumber;
}

float Motor::getPosition()
{
    return (float)stepNumber/STEPS_PER_MM;
}

#endif //motor_h
