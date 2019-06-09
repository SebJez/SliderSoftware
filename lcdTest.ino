#include "definitions.h"
#include "lcd16x2.h"

Display lcd = Display(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

void setup()
{
    lcd.writeTopLine("0123456789ABCDEF");
    lcd.writeBottomLine("FEDCBA9876543210");
}

void loop()
{
    
}
