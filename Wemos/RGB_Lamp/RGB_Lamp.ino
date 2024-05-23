#include "Server.h"
#include "LedRGB.h"

using namespace std;

WemosServer wServer;
LedRGB ledRGB(0,0,0); // Warme witte kleur 255,100,20

//const int ledPowerPin = 0;  // D3
const int sensorPin = 5;  // D0
const int boardLed = 2;     // D4

int sensorState = 0;

int red = 255;
int green = 50;
int blue = 32;

int teller = 0;

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

  wServer.verbindenWifi();

}

void loop() {

  teller++;
  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg(); // Deze functie veroorzaakt een delay
  
  received.toCharArray(buf, received.length()+1);

  //Serial.print("main: "); Serial.println(buf);

  sscanf(buf, "%d %d %d", &red, &green, &blue);

  sensorState = digitalRead(sensorPin);

  if (teller > 400) {
    Serial.print(red); Serial.print("-");
    Serial.print(green); Serial.print("-");
    Serial.print(blue); Serial.print(" ");

    Serial.println(sensorState);

    teller = 0;
  }

  if (sensorState == 1) {
    ledRGB.zetAan(red,green,blue);
    //Serial.println("aan");
    //delay(1000); // Delay hoe lang die aan moet blijven staan
  } else {
    ledRGB.zetUit();
    //Serial.println("uit");
  }

  delay(10);

}