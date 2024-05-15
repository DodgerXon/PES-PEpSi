#include "Server.h"
#include "LedRGB.h"

using namespace std;

WemosServer wServer;
LedRGB ledRGB(255,100,20); // Warme witte kleur

//const int ledPowerPin = 0;  // D3
const int sensorPin = 5;  // D0
const int boardLed = 2;     // D4

int sensorState = 0;

int red = 255;
int green = 100;
int blue = 20;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  pinMode(ledPowerPin, INPUT);
  pinMode(ledPowerPin, LOW);
  pinMode(sensorPin, INPUT_PULLUP);
  //digitalWrite(boardLed, LOW);

  //wServer.verbindenWifi();

}

void loop() {

  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg(); // Deze functie veroorzaakt een grote delay
  received.toCharArray(buf, received.length()+1);

  //Serial.print("main: ");
  //Serial.println(buf);

  sscanf(buf, "%*s %d %d %d", red, green, blue);

  Serial.print(red); Serial.print("-");
  Serial.print(green); Serial.print("-");
  Serial.print(blue); Serial.print(" ");

  sensorState = digitalRead(sensorPin);
  Serial.println(sensorState);
  
  if (sensorState == 1) {
    ledRGB.zetAan();
    //delay(1000); // Delay hoe lang die aan moet blijven staan
  } else {
    ledRGB.zetUit();
  }

  delay(100);

}