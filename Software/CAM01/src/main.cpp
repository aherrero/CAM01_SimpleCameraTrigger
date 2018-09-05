#include <Arduino.h>

#include "camera.h"
#include "display7.h"
#include "/home/aherrero/Arduino/libraries/Button/Button.h"


// Declaration
// Var
int currentMode = 0;
int selectedTimeSec_digit1 = 0;
int selectedTimeSec_digit2 = 0;
int selectedTimeSec_digit3 = 0;
int selectedTimeSec_Total_Sec = 0;
unsigned long timeCamera;
unsigned long timeButton;

// Function
void callback_ButtonOKPressed();
int IncrementTimerDigit(int selectedTime);
int DecreaseTimerDigit(int selectedTime);
void TriggerCameraRepetition();

// class
Display7 display(12, 11, 10, 9, 8, 7, 6, 13);
Camera sonyA6000;

Button buttonOK = Button(2, BUTTON_PULLDOWN);
Button buttonLeft = Button(5, BUTTON_PULLDOWN);
Button buttonRight = Button(4, BUTTON_PULLDOWN);

void setup()
{
    // Start Serial
    Serial.begin(9600);
    Serial.println("Init");

    // Init Pinout
    // Buttons alredy init as INPUT in the class Button.

    // Attach an interrupt to the ISR vector
    attachInterrupt(digitalPinToInterrupt(2), callback_ButtonOKPressed, HIGH);

    // Display 7 segments init
    display.SetPinMode();
    display.TestDisplayAll(50);
}

void loop()
{
    // State Machine
    switch(currentMode)
    {
        case 0:
        {
            // First Digit
            if(buttonLeft.isPressed())
            {
                selectedTimeSec_digit1 = DecreaseTimerDigit(selectedTimeSec_digit1);
            }
            else if(buttonRight.isPressed())
            {
                selectedTimeSec_digit1 = IncrementTimerDigit(selectedTimeSec_digit1);
            }

            display.DisplayDigit(selectedTimeSec_digit1);

            break;
        }

        case 1:
        {
            // Second Digit
            if(buttonLeft.isPressed())
            {
                selectedTimeSec_digit2 = DecreaseTimerDigit(selectedTimeSec_digit2);
            }
            else if(buttonRight.isPressed())
            {
                selectedTimeSec_digit2 = IncrementTimerDigit(selectedTimeSec_digit2);
            }

            display.DisplayDigit(selectedTimeSec_digit2 + 10);

            break;
        }

        case 2:
        {
            // Third Digit
            if(buttonLeft.isPressed())
            {
                selectedTimeSec_digit3 = DecreaseTimerDigit(selectedTimeSec_digit3);
            }
            else if(buttonRight.isPressed())
            {
                selectedTimeSec_digit3 = IncrementTimerDigit(selectedTimeSec_digit3);
            }

            display.DisplayDigit(selectedTimeSec_digit3);

            break;
        }
        case 3:
        {
            // Diff time
            unsigned long currentTime = millis();
            long diff = currentTime - timeCamera;
            float diffSec = diff / 1000.0;

            Serial.print("Timer: ");
            Serial.println(diffSec);

            // If diff bigger than selected, laucnh aghain
            if(diffSec >= selectedTimeSec_Total_Sec)
            {
                TriggerCameraRepetition();
            }

            break;
        }
        default:
        {
            break;
        }
    }

    delay(100);
}

int IncrementTimerDigit(int selectedTime)
{
    if(selectedTime < 9)
        selectedTime++;

    Serial.print("Digit value: ");
    Serial.println(selectedTime);

    return selectedTime;
}

int DecreaseTimerDigit(int selectedTime)
{
    if(selectedTime > 0)
        selectedTime--;

    Serial.print("Digit value: ");
    Serial.println(selectedTime);

    return selectedTime;
}

void TriggerCameraRepetition()
{
    display.DiplayPoint();
    Serial.println("Shutter");
    sonyA6000.SonyShutter();
    timeCamera = millis();
}

void callback_ButtonOKPressed()
{
    Serial.println("Button OK Interrupt");

    unsigned long currentTime = millis();

    int timeBetween2ButtonOK = 1000;    //1000 ms
    if(currentTime > timeButton + timeBetween2ButtonOK)  // 2s between pushbutton
    {
        if(buttonOK.isPressed())
        {
            timeButton = millis();    // Update timebutton to not allow push the button in X time

            Serial.println("OK allowed");
            if(currentMode != 3)
            {
                currentMode++;
                if(currentMode == 3)
                {
                    // Just changed to RUN MODE
                    display.ClearDisplay();
                    selectedTimeSec_Total_Sec = selectedTimeSec_digit1 * 100 + selectedTimeSec_digit2 * 10 + selectedTimeSec_digit3;
                    Serial.print("Time selected: ");
                    Serial.println(selectedTimeSec_Total_Sec);
                    timeCamera = millis();      // Update timer for trigger

                }
            }
            else
            {
                currentMode = 0;
            }
        }
    }
    else
    {
        Serial.print("[Warning] Time minimum between two pulsations: ");
        Serial.println(timeBetween2ButtonOK);
    }

    // Delay a little bit to avoid bouncing
    // Careful, delay in a callback
    delay(50);
}
