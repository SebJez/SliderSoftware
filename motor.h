#ifndef motor_h
#define motor_h

class Motor
{
    long move(long steps);
    float move(float distance_mm);
    float setSpeed(float speed_mm_per_second);
    long getStep();
    float getPosition();
    Motor(int pinA1, int pinA2, int pinB1, int pinB2, long steps_per_mm, float speed_mm_per_second);
    

    private:
        void makeStep(bool clockwise);
        long stepNumber = 0;
        byte phase = 0; //overflow intended 
        bool stop_flag = false;
        unsigned long interval;
        unsigned long last_step_time = 0;
        long steps_per_mm;
        int pinA1;
        int pinA2;
        int pinB1;
        int pinB2;
        bool flip_direction;
        bool enable_endstops;
        long max_steps;

Motor::Motor(int pinA1, int pinA2, int pinB1, int pinB2, long steps_per_mm, \
  float speed_mm_per_second, bool flip_direction = false, bool enable_endstops = false, long max_steps = LONG_MAX):\
  pinA1(pinA1),pinA2(pinA2),pinB1(pinB1),pinB2(pin_B2), \
  steps_per_mm(steps_per_mm),flip_direction(flip_direction),enable_endstops(enable_endstops)
{
    pinMode(pinA1, OUTPUT);
    pinMode(pinA2, OUTPUT);
    pinMode(pinB1, OUTPUT);
    pinMode(pinB2, OUTPUT);
    setSpeed(speed_mm_per_second);
}

void Motor::setSpeed(float speed_mm_per_second)
{
    interval = 1e6 / steps_per_mm / speed_mm_per_second;
}

long Motor::move(long steps)
{
    long steps_to_do = steps;
    
   if(enable_endstops)
   {
        long endpos = stepNumber+steps_to_do;
        if (endpos >= max_steps) steps_to_do = max_steps - stepNumber;
        else if (endpos < 0) steps_to_do = - stepNumber;
   }

    long remaining_steps = abs(steps_to_do);
    
    bool dir = (distance >= 0) ? 1 : 0;
    if(flip_direction) dir = !dir;

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
    return stepNumber;
}

float Motor::move(float distance_mm)
{
    long steps = distance_mm * steps_per_mm;
    return ((float)move(steps))/((float)steps_per_mm);
}

long Motor::getStep()
{
    return stepNumber;
}

float Motor::getPosition()
{
    return (float)stepNumber/steps_per_mm;
}

#endif //motor_h
