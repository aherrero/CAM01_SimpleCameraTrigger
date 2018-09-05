#ifndef Display7_h
#define Display7_h

#include "Arduino.h"

static const byte SEGMENT_CODE_ANODE[20][8] = {
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

class Display7
{
public:
    Display7(int pin_a, int pin_b,
                int pin_c, int pin_d,
                int pin_e, int pin_f,
                int pin_g, int pin_dt);

    void SetPinMode();
    void DisplayDigit(int digit);
    void ClearDisplay();
    void TestDisplayAll();

private:
    int segPins[8];
};

#endif
