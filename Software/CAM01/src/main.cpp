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
static const bool SERIAL_COMM_ENABLE = true;

// Function
void callback_ButtonOKPressed();
int IncrementTimerDigit(int selectedTime);
int DecreaseTimerDigit(int selectedTime);
void TriggerCameraRepetition();

// class
Display7 display(7, 6, 10, 9, 8, 12, 11, 13);
Camera sonyA6000;

Button buttonOK = Button(2, BUTTON_PULLDOWN);
Button buttonLeft = Button(5, BUTTON_PULLDOWN);
Button buttonRight = Button(4, BUTTON_PULLDOWN);

void setup()
{
    // Start Serial
    if(SERIAL_COMM_ENABLE)
    {
        Serial.begin(9600);
        Serial.println("Init");
    }

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
    // The state will change between configuration mode and run mode
    // 3 state mode in configuration mode; choose the 3 digits for the seconds:
    // The first digit will be multiply by 100, the second by 10 and third by 1.
    // Example:
    // Mode 0: 1
    // Mode 1: 2
    // Mode 2; 3
    // Mode RUN
    // The time selected is 123 seconds. The RUN Mode will trigger the camera
    // each 123 Seconds. If Button OK is pressed during RUN Mode, the State will
    // be changed to initial Mode (0)
    switch(currentMode)
    {
        case 0:
        {
            // Select the first digit for seconds
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

            display.DisplayDigit(selectedTimeSec_digit2 + 10);  //Show the number with the dot point (+10)

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
            // Diff time between now and the time when button ok was pressed
            unsigned long currentTime = millis();
            long diff = currentTime - timeCamera;
            float diffSec = diff / 1000.0;

            // Show the timer counter
            if(SERIAL_COMM_ENABLE)
            {
                Serial.print("Timer: ");
                Serial.println(diffSec);
            }

            // If the difference between both timer are bigger or equal than the time selected
            // Trigger the camera signal and restart the timer
            if(diffSec >= selectedTimeSec_Total_Sec)
            {
                TriggerCameraRepetition();
                timeCamera = millis();
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

    if(SERIAL_COMM_ENABLE)
    {
        Serial.print("Digit value: ");
        Serial.println(selectedTime);
    }

    return selectedTime;
}

int DecreaseTimerDigit(int selectedTime)
{
    if(selectedTime > 0)
        selectedTime--;

    if(SERIAL_COMM_ENABLE)
    {
        Serial.print("Digit value: ");
        Serial.println(selectedTime);
    }

    return selectedTime;
}

void TriggerCameraRepetition()
{
    // Display some miliseconds the point before shutting
    display.DiplayPoint();

    // Show msg
    if(SERIAL_COMM_ENABLE)
        Serial.println("Shutter");

    // Camera trigger. Turn ON the IR Led with the shotting signal
    sonyA6000.SonyShutter();
}

void callback_ButtonOKPressed()
{
    if(SERIAL_COMM_ENABLE)
        Serial.println("Interrupt Button OK");

    unsigned long currentTime = millis();

    // To avoid pressing several times the button OK in the same seconds
    // Counter for not allowing press the button in 1 sec.
    int timeBetween2ButtonOK = 1000;    //1000 ms
    if(currentTime > timeButton + timeBetween2ButtonOK)  // 2s between pushbutton
    {
        if(buttonOK.isPressed())
        {
            timeButton = millis();    // Update timebutton to not allow push the button in X time

            if(SERIAL_COMM_ENABLE)
                Serial.println("OK allowed");
            if(currentMode != 3)
            {
                currentMode++;
                if(currentMode == 3)
                {
                    // Just changed to RUN MODE
                    display.ClearDisplay();

                    // Calculate total time configured
                    selectedTimeSec_Total_Sec = selectedTimeSec_digit1 * 100 + selectedTimeSec_digit2 * 10 + selectedTimeSec_digit3;

                    // Show in UART if enabled
                    if(SERIAL_COMM_ENABLE)
                    {
                        Serial.print("Time selected: ");
                        Serial.println(selectedTimeSec_Total_Sec);
                    }

                    // Restart timer counter
                    timeCamera = millis();      // Update timer for trigger

                }
            }
            else
            {
                // If Arduino in RUN_MODE, when the Button OK is pressed
                // Return to the state 0 (Select the first digit)
                currentMode = 0;
            }
        }
    }
    else
    {
        if(SERIAL_COMM_ENABLE)
        {
            Serial.print("[Warning] Time minimum between two pulsations: ");
            Serial.println(timeBetween2ButtonOK);
        }
    }

    // Delay a little bit to avoid bouncing
    // Careful, delay in a callback
    delay(50);
}
