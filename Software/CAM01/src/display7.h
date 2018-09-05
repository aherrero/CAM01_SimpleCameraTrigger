#ifndef Display7_h
#define Display7_h

#include "Arduino.h"

static const int DISPLAY_MAX_DIGIT = 21;

static const byte SEGMENT_CODE_ANODE[22][8] = {
//  a  b  c  d  e  f  g  .
  { 0, 0, 0, 0, 0, 0, 1, 1},  // 0
  { 1, 0, 0, 1, 1, 1, 1, 1},  // 1
  { 0, 0, 1, 0, 0, 1, 0, 1},  // 2
  { 0, 0, 0, 0, 1, 1, 0, 1},  // 3
  { 1, 0, 0, 1, 1, 0, 0, 1},  // 4
  { 0, 1, 0, 0, 1, 0, 0, 1},  // 5
  { 0, 1, 0, 0, 0, 0, 0, 1},  // 6
  { 0, 0, 0, 1, 1, 1, 1, 1},  // 7
  { 0, 0, 0, 0, 0, 0, 0, 1},  // 8
  { 0, 0, 0, 0, 1, 0, 0, 1},  // 9
  { 0, 0, 0, 0, 0, 0, 1, 0},   // 10 -> 0.
  { 1, 0, 0, 1, 1, 1, 1, 0},  // 11 -> 1.
  { 0, 0, 1, 0, 0, 1, 0, 0},  // 12 -> 2.
  { 0, 0, 0, 0, 1, 1, 0, 0},  // 13 -> 3.
  { 1, 0, 0, 1, 1, 0, 0, 0},  // 14 -> 4.
  { 0, 1, 0, 0, 1, 0, 0, 0},  // 15 -> 5.
  { 0, 1, 0, 0, 0, 0, 0, 0},  // 16 -> 6.
  { 0, 0, 0, 1, 1, 1, 1, 0},  // 17 -> 7.
  { 0, 0, 0, 0, 0, 0, 0, 0},  // 18 -> 8.
  { 0, 0, 0, 0, 1, 0, 0, 0},  // 19 -> 9.
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 20 -> .
  { 1, 1, 1, 1, 1, 1, 1, 1}  // 21 -> ""
};

class Display7
{
public:
    Display7(int pin_a, int pin_b,
                int pin_c, int pin_d,
                int pin_e, int pin_f,
                int pin_g, int pin_dt);

    void SetPinMode();
    int DisplayDigit(int digit);
    void ClearDisplay();
    void DiplayPoint(int delayMs = 10);
    void TestDisplayAll(int delayMs = 200);

private:
    int segPins[8];
};

#endif
