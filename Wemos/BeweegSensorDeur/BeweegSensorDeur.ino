#include "WemosServer.h"

using namespace std;

WemosServer wServer;

const int sensorPin = 5;  // D0
const int boardLed = 2;   // D4

int sensorState = 0;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  pinMode(sensorPin, INPUT_PULLUP);
  digitalWrite(boardLed, LOW);

  wServer.verbindenWifi();
}

void loop() {

  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg(); //Leest het binnen gekomen bericht
  
  received.toCharArray(buf, received.length()+1);

  sensorState = digitalRead(sensorPin);
//stuurt de waarde van de bewegingssensor terug aan de pie om in het document aan te passen
  if (received == "status") { 
    if (sensorState) {
      wServer.sendMsg("Aan");
    } else {
      wServer.sendMsg("Uit");
    }
  }
// Zet de pin op de Wemos aan of uit aan de hand van of er beweging is gedetecteerd
  if (sensorState) {
    digitalWrite(boardLed, HIGH);
  } else {
    digitalWrite(boardLed, LOW);
  }
}
