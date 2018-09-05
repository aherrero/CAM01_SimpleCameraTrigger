#include <Arduino.h>
// #include <IRremote.h>
#include "/home/aherrero/Arduino/libraries/IRremote/IRremote.h"

// Camera
IRsend irsend;

static const unsigned long SONY_SHUTTER = 0xB4B8F;
static const unsigned long SONY_SHUTTER_T2 = 0xECB8F;
static const unsigned long SONY_VIDEO = 0x12B8F;

static const unsigned long SONY_DISP = 0x28B8F;
static const unsigned long SONY_MENU = 0x1CB8F;
static const unsigned long SONY_MENU_UP = 0x5CB8F;
static const unsigned long SONY_MENU_DOWN = 0xDCB8F;
static const unsigned long SONY_MENU_RIGHT = 0xFCB8F;
static const unsigned long SONY_MENU_LEFT = 0x7CB8F;
static const unsigned long SONY_MENU_OK = 0x9CB91;

static const unsigned long SONY_ZOOM_PLUS = 0x52B8F;
static const unsigned long SONY_ZOOM_LESS = 0xD2B8F;

void sendToSony(unsigned long hexCode)
{
    for (int i=0; i<3; i++)
    {
        irsend.sendSony(hexCode, 20);
        delay(40);
    }
}


// Pinout
int buttonOKPin = 2;
int buttonLeftPin = 5;
int buttonRightPin = 4;

// VAR
int timerCounter = 0;
int MODE = 0;

// 7-Segments
int segPins[] = {12, 11, 10, 9, 8, 7, 6, 13 };   // { a b c d e f g . )

byte segCode[20][8] = {
//  a  b  c  d  e  f  g  .
  { 0, 0, 0, 0, 0, 0, 1, 0},  // 0
  { 1, 0, 0, 1, 1, 1, 1, 0},  // 1
  { 0, 0, 1, 0, 0, 1, 0, 0},  // 2
  { 0, 0, 0, 0, 1, 1, 0, 0},  // 3
  { 1, 0, 0, 1, 1, 0, 0, 0},  // 4
  { 0, 1, 0, 0, 1, 0, 0, 0},  // 5
  { 0, 1, 0, 0, 0, 0, 0, 0},  // 6
  { 0, 0, 0, 1, 1, 1, 1, 0},  // 7
  { 0, 0, 0, 0, 0, 0, 0, 0},  // 8
  { 0, 0, 0, 0, 1, 0, 0, 0},  // 9
  { 1, 1, 1, 1, 1, 1, 1, 1},   // 10 -> .
  { 1, 0, 0, 1, 1, 1, 1, 1},  // 11 -> 1.
  { 0, 0, 1, 0, 0, 1, 0, 1},  // 12 -> 2.
  { 0, 0, 0, 0, 1, 1, 0, 1},  // 13 -> 3.
  { 1, 0, 0, 1, 1, 0, 0, 1},  // 14 -> 4.
  { 0, 1, 0, 0, 1, 0, 0, 1},  // 15 -> 5.
  { 0, 1, 0, 0, 0, 0, 0, 1},  // 16 -> 6.
  { 0, 0, 0, 1, 1, 1, 1, 1},  // 17 -> 7.
  { 0, 0, 0, 0, 0, 0, 0, 1},  // 18 -> 8.
  { 0, 0, 0, 0, 1, 0, 0, 1}  // 19 -> 9.
};

void displayDigit(int digit)
{
  for (int i=0; i < 8; i++)
  {
    digitalWrite(segPins[i], segCode[digit][i]);
  }
}

void testDisplayAll()
{
    // 7 segement test. Display ALL
    for (int i=0; i < 20; i++)
    {
        displayDigit(i);
        delay(200);
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello");

    // Init pin INPUT / OUTPUT

    // initialize the pushbutton pin as an input:
    pinMode(buttonOKPin, INPUT);
    pinMode(buttonLeftPin, INPUT);
    pinMode(buttonRightPin, INPUT);

    // 7 segments
    for (int i=0; i < 8; i++)
    {
      pinMode(segPins[i], OUTPUT);
    }
}

void loop()
{
    // read the state of the pushbutton value:
    int buttonOK = digitalRead(buttonOKPin);
    int buttonLeft = digitalRead(buttonLeftPin);
    int buttonRight = digitalRead(buttonRightPin);
    Serial.print(buttonLeft);
    Serial.print(buttonRight);
    Serial.println(buttonOK);

    switch(MODE)
    {
        case 0:
        {
            if(buttonLeft == HIGH)
            {
                if(timerCounter > 0)
                    timerCounter--;
            }
            else if(buttonRight == HIGH)
            {
                if(timerCounter < 9)
                    timerCounter++;
            }
            else if (buttonOK == HIGH)
            {
                MODE = 1;
            }

            displayDigit(timerCounter);
            delay(100);

            break;
        }
        case 1:
        {
            // turn LED on:
            sendToSony(SONY_SHUTTER);

            delay(timerCounter * 1000);

            if (buttonOK == HIGH)
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
