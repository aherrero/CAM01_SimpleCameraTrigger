/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

void setup()
{
  
}

void loop() {
  delay(5000); //5 second delay between each signal burst
  for (int i=0; i<3; i++){ 

      // irsend.sendSony(0xB4B8F, 20); // Shutter | take photo

      // irsend.sendSony(0x12B8F, 20); // Start | stop video recording 

      // irsend.sendSony(0x28B8F, 20); // Display change cycles round  // Ok

      irsend.sendSony(0xECB8F, 20); // 2s


//      Photo     740239    B4B8F   // Shutter | take photo
//      Photo     969615    ECB8F   // Shutter x2 sec| take photo
//
//      VID       76687     12B8F   // Start | stop video recording
//      
//      DISP      166799    28B8F   // Display change cycles round
//      
//      Menu      117647    1CB8F   // Enter menu | leave menu
//      
//      MenuU     379791    5CB8F   // Menu up
//      
//      menuD     904079    DCB8F   // Menu down
//      
//      menuR     1035151   FCB8F   // Menu right
//      
//      menuL     510863    7CB8F   // Menu left
//      
//      OK        641937    9CB91   // Menu OK
//      
//      Z+        338831    52B8F   // Zoom in
//      
//      Z-        863119    D2B8F   // Zoom out
      

      delay(40);

  }

  
	delay(5000); //5 second delay between each signal burst
}
