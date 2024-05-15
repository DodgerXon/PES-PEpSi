#include "ledRGB.h"

LedRGB::LedRGB(int r, int g, int b ) : red(r), green(g), blue(b) {
}
LedRGB::~LedRGB(){}


void LedRGB::zetAan() {

  pinMode(ledPowerPin, HIGH);

  if (redPrev != red || greenPrev != green || bluePrev != blue) { // Checks if the colors have changed.
    ledTurnedOn = true;
  }

  if (ledTurnedOn) {
    double i = 20.0;

    while ( i > 1.0 ) { // Smooth transition
      analogWrite(ledR, red * 3 / i);
      analogWrite(ledG, green * 3 / i);
      analogWrite(ledB, blue * 3 / i);
      i -= 0.1;
    }
    ledTurnedOn = false;
  }
  
  redPrev = red;
  greenPrev = green;
  bluePrev = blue;
}

void LedRGB::zetUit() {
  pinMode(ledPowerPin, LOW);
  ledTurnedOn = true;
}