#include "display7.h"

Display7::Display7(int pin_a, int pin_b,
                    int pin_c, int pin_d,
                    int pin_e, int pin_f,
                    int pin_g, int pin_dt)
{
    // int segPins[] = {12, 11, 10, 9, 8, 7, 6, 13 };   // { a b c d e f g . )

    segPins[0] = pin_a;
    segPins[1] = pin_b;
    segPins[2] = pin_c;
    segPins[3] = pin_d;

    segPins[4] = pin_e;
    segPins[5] = pin_f;
    segPins[6] = pin_g;
    segPins[7] = pin_dt;
}

void Display7::SetPinMode()
{
    for (int i=0; i < 8; i++)
    {
        pinMode(segPins[i], OUTPUT);
    }
}

int Display7::DisplayDigit(int digit)
{
    if(digit > DISPLAY_MAX_DIGIT)
        return -1;

    for (int i=0; i < 8; i++)
    {
        digitalWrite(segPins[i], SEGMENT_CODE_ANODE[digit][i]);
    }

    return 0;
}

void Display7::ClearDisplay()
{
    DisplayDigit(21);
}

void Display7::DiplayPoint(int delayMs)
{
    DisplayDigit(20);
    delay(delayMs);
    ClearDisplay();
}

void Display7::TestDisplayAll(int delayMs)
{
    // 7 segment test. Display ALL
    for (int i=0; i < DISPLAY_MAX_DIGIT + 1; i++)
    {
        DisplayDigit(i);
        delay(delayMs);
    }
}
