#include <Arduino.h>

#include "camera.h"
#include "display7.h"
#include "/home/aherrero/Arduino/libraries/Button/Button.h"


// VAR
int timerCounter = 0;
int MODE = 0;

// class
Display7 display(12, 11, 10, 9, 8, 7, 6, 13);

Button buttonOK = Button(2, BUTTON_PULLDOWN);
Button buttonLeft = Button(5, BUTTON_PULLDOWN);
Button buttonRight = Button(4, BUTTON_PULLDOWN);

void setup()
{
    // Start Serial
    Serial.begin(9600);
    Serial.println("Hello");

    // Init Pinout
    // Buttons alredy init as INPUT in the class Button.

    // Display 7 segments init
    display.SetPinMode();
}

void loop()
{
    // read the state of the pushbutton value:

    switch(MODE)
    {
        case 0:
        {
            if(buttonRight.isPressed())
            {
                if(timerCounter > 0)
                    timerCounter--;
            }
            else if(buttonLeft.isPressed())
            {
                if(timerCounter < 9)
                    timerCounter++;
            }
            else if(buttonOK.isPressed())
            {
                MODE = 1;
            }

            display.DisplayDigit(timerCounter);
            delay(100);

            break;
        }
        case 1:
        {
            display.ClearDisplay();

            Camera sonyA6000;
            sonyA6000.SonyShutter();

            delay(timerCounter * 1000);

            if(buttonOK.isPressed())
            {
                MODE = 0;
            }
            break;
        }
        default:
        {
            break;
        }

    }

}
