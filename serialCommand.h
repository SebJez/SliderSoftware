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
                    Serial.print("K ");
                    Serial.println(String(1.f/STEPS_PER_MM));
                    Serial.print("L ");
                    Serial.println(String(stepper->stepsToMm(MAX_STEPS)));
                    Serial.print("S ");
                    Serial.println(String(stepper->getSpeed()));
                    Serial.print("X ");
                    Serial.println(String(stepper->stepsToMm(stepper->getStep())));
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
                    Serial.println("H");
                    break;
                }
            case 'X':
                {
                    float millimeters = command->toFloat();
                    long steps = stepper->mmToSteps(millimeters);
                    Serial.print("X ");
                    Serial.println(String(stepper->stepsToMm(stepper->move(steps))));
                    break;
                }
            case 'S':
                {
                    float speed = command->toFloat();
                    Serial.print("S ");
                    Serial.println(String(stepper->setSpeed(speed)));
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
