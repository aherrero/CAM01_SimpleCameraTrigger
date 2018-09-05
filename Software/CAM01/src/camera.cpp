#include "camera.h"

Camera::Camera()
{

}

// General Function
void Camera::SendCodeToSony(unsigned long hexCode)
{
    for (int i=0; i<3; i++)
    {
        irsend.sendSony(hexCode, 20);
        delay(40);
    }
}


void Camera::SonyShutter()
{
    SendCodeToSony(SONY_SHUTTER);
}

void Camera::SonyShutterT2()
{
    SendCodeToSony(SONY_SHUTTER_T2);
}
