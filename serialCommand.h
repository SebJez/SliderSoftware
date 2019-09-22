#ifndef serialCommand_h
#define serialCommand_h
#include "definitions.h"
#include "motor.h"

class SerialCommand
{
    Motor* stepper;
     private:
           void printInfo()
           {
                    Serial.print("steps per mm\t");
                    Serial.println(String(STEPS_PER_MM));
                    Serial.print("max steps\t");
                    Serial.println(String(MAX_STEPS));
                    Serial.print("S");
                    Serial.println(String(stepper->getSpeed()));
                    Serial.print("X");
                    Serial.println(String(stepper->getStep()));
           };

           void interpretCommand(String* command)
        {
            char commandWord = command->charAt(0);
            command->remove(0,1);
            switch (commandWord)
            {
            case 'H':
                {
                    stepper->home();
                    break;
                }
            case 'X':
                {
                    long steps = command->toInt();
                    Serial.print("X");
                    Serial.println(String(stepper->move(steps)));
                    break;
                }
            case 'S':
                {
                    float speed = command->toFloat();
                    stepper->setSpeed(speed);
                    break;
                }
            case 'I':
                {   
                    printInfo();
                    break;
                }
            }
        
        }

    public:

    SerialCommand(Motor* stepper_):stepper(stepper_){;}

    void run()
    {        
        Serial.begin(9600);
        while(Serial.read()!='0')
        {
            printInfo();
            if(digitalRead(PIN_CANCEL)==LOW) return;
            delay(300);
        }

        while (digitalRead(PIN_CANCEL)!=LOW)
        {
            if(Serial.available()<=0)
            {
                delay(300);
            }
            else
            {
                String command = Serial.readStringUntil('\n');
                interpretCommand(&command);
            }
            
        }
        return;
    }

    
}; // class SerialCommand






#endif
