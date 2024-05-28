#include "Server.h"
#include "LedRGB.h"

using namespace std;

WemosServer wServer;
LedRGB ledRGB(0,0,0); // Warme witte kleur 255,100,20

const int boardLed = 2; // D4

int red = 255;
int green = 50;
int blue = 32;

unsigned long previousMillis = 0;
const long interval = 5000;  // Interval in milliseconds

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  pinMode(ledPowerPin, INPUT);
  pinMode(ledPowerPin, LOW);
  digitalWrite(boardLed, LOW);

  wServer.verbindenWifi();
}

void loop() {

  unsigned long currentMillis = millis();
  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg();
  
  received.toCharArray(buf, received.length()+1); // Zet het commando om naar een char array

  sscanf(buf, "%d %d %d", &red, &green, &blue); // Zet het commando om naar de kleur waardes

  // Checkt of de status van de beweegsenser aan is via de client PI.
  if (received == "Aan") {
      ledRGB.zetAan(red,green,blue);
  } else {
      if (currentMillis - previousMillis >= interval) {
        ledRGB.zetUit();
        previousMillis = currentMillis;
      }
  }
}