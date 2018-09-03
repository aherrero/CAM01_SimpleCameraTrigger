#include <IRremote.h>

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
const int buttonPin = 2;
const int ledPin =  13;

void sendToSony(unsigned long hexCode)
{
    for (int i=0; i<3; i++)
    {
        irsend.sendSony(hexCode, 20);
        delay(40);
    }
}

void setup()
{
    // put your setup code here, to run once:

    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:

    // read the state of the pushbutton value:
    int buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
        // turn LED on:
        digitalWrite(ledPin, HIGH);

        sendToSony(SONY_SHUTTER_T2);
    }
    else
    {
        // turn LED off:
        digitalWrite(ledPin, LOW);
    }

    delay(500);
}

