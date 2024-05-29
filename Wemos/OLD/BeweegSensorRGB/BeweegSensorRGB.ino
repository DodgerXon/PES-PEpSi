#include "Server.h"

using namespace std;

WemosServer wServer;

const int sensorPin = 5;  // D0
const int boardLed = 2;   // D4

int sensorState = 0;

int teller = 0;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  pinMode(sensorPin, INPUT_PULLUP);
  digitalWrite(boardLed, LOW);

  wServer.verbindenWifi();

}

void loop() {

  teller++;
  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg(); // Deze functie veroorzaakt een delay
  
  received.toCharArray(buf, received.length()+1);

  sensorState = digitalRead(sensorPin);

  if (received == "status") {
    if (sensorState) {
      wServer.sendMsg("Aan");
    } else {
      wServer.sendMsg("Uit");
    }
  }

  if (sensorState) {
    digitalWrite(boardLed, HIGH);
  } else {
    digitalWrite(boardLed, LOW);
  }

  //Serial.print("Sensor: "); Serial.println(sensorState);

  delay(10);
}