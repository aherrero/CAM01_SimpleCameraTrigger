#ifndef Camera_h
#define Camera_h

#include "Arduino.h"
#include <IRremote.h>

// Const
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

class Camera
{
public:
    Camera();

    void SonyShutter();
    void SonyShutterT2();

private:
    IRsend irsend;  // Declare IR library

    void SendCodeToSony(unsigned long hexCode);

};

#endif
