#include <Arduino.h>
#include "/home/aherrero/Arduino/libraries/IRremote/IRremote.h"
//#include <IRremote.h>

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

// Pinout
const int buttonOK = 0;
const int buttonLeft = 1;
const int buttonRight = 2;

// 7-Segments
int segPins[] = {12, 11, 10, 9, 8, 7, 6, 13 };   // { a b c d e f g . )

byte segCode[20][8] = {
//  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 8
  { 1, 1, 1, 1, 0, 1, 1, 0},  // 9
  { 0, 0, 0, 0, 0, 0, 0, 1},   // 10 -> .
  { 0, 1, 1, 0, 0, 0, 0, 1},  // 11 -> 1.
  { 1, 1, 0, 1, 1, 0, 1, 1},  // 12 -> 2.
  { 1, 1, 1, 1, 0, 0, 1, 1},  // 13 -> 3.
  { 0, 1, 1, 0, 0, 1, 1, 1},  // 14 -> 4.
  { 1, 0, 1, 1, 0, 1, 1, 1},  // 15 -> 5.
  { 1, 0, 1, 1, 1, 1, 1, 1},  // 16 -> 6.
  { 1, 1, 1, 0, 0, 0, 0, 1},  // 17 -> 7.
  { 1, 1, 1, 1, 1, 1, 1, 1},  // 18 -> 8.
  { 1, 1, 1, 1, 0, 1, 1, 1}  // 19 -> 9.
};

void displayDigit(int digit)
{
  for (int i=0; i < 8; i++)
  {
    digitalWrite(segPins[i], segCode[digit][i]);
  }
}

void sendToSony(unsigned long hexCode)
{
    for (int i=0; i<3; i++)
    {
        //irsend.sendSony(hexCode, 20);
        delay(40);
    }
}

void setup()
{
    // Init pin INPUT / OUTPUT

    // initialize the pushbutton pin as an input:
    pinMode(buttonOK, INPUT);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);

    // 7 segments
    for (int i=0; i < 8; i++)
    {
      pinMode(segPins[i], OUTPUT);
    }
}

void loop()
{
    // read the state of the pushbutton value:
    int buttonState = digitalRead(buttonOK);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
        // turn LED on:
        sendToSony(SONY_SHUTTER_T2);

        displayDigit(10);   // Show Decimal point
    }
    else
    {
        displayDigit(0);
    }

    delay(500);
}
