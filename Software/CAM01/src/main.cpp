#include <Arduino.h>
#include <LowPower.h>
#include <Button.h>

#include "camera.h"
#include "display7.h"


// Declaration
// Var
int currentMode = 0;
int selectedTimeSec_digit1 = 0;
int selectedTimeSec_digit2 = 0;
int selectedTimeSec_digit3 = 0;
int selectedTimeSec_Total_Sec = 0;
unsigned long timeCamera;
unsigned long currentCounter = 0;
unsigned long timeButton;
static const bool SERIAL_COMM_ENABLE = false;

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
            // idle 1 sec to save power (in a bare atmega, 8.7mA vs 10mA)
            // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_ON, SPI_OFF, USART0_OFF, TWI_OFF);

            // power down, 3.9mA vs 10mA
            if(selectedTimeSec_Total_Sec != 0)
                LowPower.powerDown(SLEEP_1S, ADC_ON, BOD_OFF);  //ADC_ON Because we need the external interrupt ON

            // Diff time between now and the time when button ok was pressed
            // unsigned long currentTime = millis();
            currentCounter = currentCounter + 1;

            // Show the timer counter
            if(SERIAL_COMM_ENABLE)
            {
                Serial.print("Timer: ");
                Serial.println(currentCounter);
            }

            // If the difference between both timer are bigger or equal than the time selected
            // Trigger the camera signal and restart the timer
            if(currentCounter >= selectedTimeSec_Total_Sec)
            {
                TriggerCameraRepetition();
                currentCounter = 0;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    delay(10);
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

    delay(100);

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

    delay(100);

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
                // timeCamera = millis();      // Update timer for trigger
                currentCounter = 0;

            }
        }
        else
        {
            // If Arduino in RUN_MODE, when the Button OK is pressed
            // Return to the state 0 (Select the first digit)
            currentMode = 0;
        }
    }

    // Delay a little bit to avoid bouncing
    // Careful, delay in a callback
    delay(250);
}
