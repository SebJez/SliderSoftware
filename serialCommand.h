#ifndef serialCommand_h
#define serialCommand_h
#include "definitions.h"
#include "motor.h"

namespace SerialCommand
{
           void interpretCommand(Motor* stepper, String* command)
        {
            char commandWord = command->charAt(0);
            command->remove(0);
            switch (commandWord)
            {
            case 'H':
                //stepper->home()
                Serial.println("Homing");
                break;

            case 'M':
                long steps = command->toInt();
                //stepper->move(steps);
                Serial.println("Move"+String(steps));
                break;
            
            case 'S':
            
                float speed = command->toFloat();
                Serial.println("Speed"+String(speed));
                //stepper->setSpeed(speed);
                break;

            case 'I':
                Serial.print("steps per mm\t");
                Serial.println(String(STEPS_PER_MM));
                Serial.print("max steps\t");
                Serial.println(String(MAX_STEPS));
                Serial.print("speed");
                Serial.println(String(stepper->getSpeed()));
                break;
            }
        
        }

    void run(Motor* stepper)
    {
        Serial.begin(9600);
        
        while(Serial.read()!='0')
        {
            Serial.print("steps per mm\t");
            Serial.println(String(STEPS_PER_MM));
            Serial.print("max steps\t");
            Serial.println(String(MAX_STEPS));
            Serial.print("speed");
            Serial.println(String(stepper->getSpeed()));
            if(digitalRead(PIN_CANCEL)==LOW) return 0;
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
                interpretCommand(stepper, &command);
            }
            
        }
        
 
        
    }

    
} // namespace SerialCommand






#endif
