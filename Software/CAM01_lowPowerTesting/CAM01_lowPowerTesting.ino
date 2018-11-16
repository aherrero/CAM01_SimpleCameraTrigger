// **** INCLUDES *****
#include "LowPower.h"
unsigned long currentTime;
unsigned long currentTimeOld;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);

    currentTimeOld = millis();
}

void loop()
{
    // IDLE
    LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
        SPI_OFF, USART0_OFF, TWI_OFF);

    // POWER DOWN
    // LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);

    //delay(2000);

    // AHE: Normally, if timer2 working, this will blink
    currentTime = millis();
    if(currentTime -  currentTimeOld > 1000)
    {
        currentTimeOld = millis();
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(200);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(200);
    }
}
