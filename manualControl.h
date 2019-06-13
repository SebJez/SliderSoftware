#ifndef manualControl_h
#define manualControl_h
#include "definitions.h"
#include "setValue.h"
#include "menu.h"
#include "motor.h"
byte manualControl()
{
    String manualControlSettings[] = {T_MANUAL_STEP, T_MANUAL_MOVE};
    byte manualControllSettingsNo = 2;

    Menu manualControlMenu = Menu(manualControlSettings,manualControllSettingsNo,\
                                    PIN_ENCODER_PRESS,PIN_CANCEL,&encoder,&lcd);
    
    long possibleSteps[] = {1,5,25,125,250};
    String possibleMm[] = {"0.04mm","0.2mm","1mm","5mm","10mm"};

    Menu manualControlStepsMenu = Menu(possibleMm,5,PIN_ENCODER_PRESS,PIN_CANCEL,&encoder,&lcd);

    byte subprogram = manualControlMenu.run();

    long steps = 5L;
    while(true)
    {
        switch (subprogram)
        {
        case 0x00:
        
        byte selectSteps = manualControlStepsMenu.run();
        if(selectSteps < 0x05) steps = possibleSteps[selectSteps];
        break;
        
        case 0x01:
        manualControlMove();
        break;

        case 0xFF:
        return 0xFF;
        break;
        }
    }
}

#endif