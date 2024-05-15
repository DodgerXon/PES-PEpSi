#ifndef LEDRGB_H
#define LEDRGB_H

#include <Arduino.h>

const int ledR = 12; // D6
const int ledG = 13; // D7
const int ledB = 15; // D8
const int ledPowerPin = 0;  // D3

using namespace std;

class LedRGB {
public:
  LedRGB(int,int,int);
  ~LedRGB();
  void zetAan();
  void zetUit();

private:
  int red;
  int green;
  int blue;
  int redPrev;
  int greenPrev;
  int bluePrev;
  bool ledTurnedOn;
};

#endif
