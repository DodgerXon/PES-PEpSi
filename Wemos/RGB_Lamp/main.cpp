#include "Server.h"

using namespace std;

WemosServer wServer;

const int ledR = 12; // D6
const int ledG = 13; // D7
const int ledB = 15; // D8

const int buttonPin1 = 16;  // D0
const int buttonPin2 = 4;   // D2
const int ledPowerPin = 0;  // D3
const int boardLed = 2;     // D4

int rgb[3] = {0,0,0};

void sendRGBCode(int rgb[]) {

  analogWrite(ledR, rgb[0] * 4);
  analogWrite(ledG, rgb[1] * 4);
  analogWrite(ledB, rgb[2] * 4);

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
}

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  pinMode(ledPowerPin, INPUT);

  digitalWrite(boardLed, LOW);
  digitalWrite(ledPowerPin, LOW);

  wServer.verbindenWifi();

}

void loop() {

  char buf[20];

  wServer.startServer();
  String received = wServer.receivedMsg();
  received.toCharArray(buf, received.length()+1);

  //Serial.print("main: ");
  //Serial.println(buf);

  sscanf(buf, "%*s %d %d %d", &rgb[0], &rgb[1], &rgb[2]);

  Serial.print(rgb[0]);
  Serial.print("-");
  Serial.print(rgb[1]);
  Serial.print("-");
  Serial.println(rgb[2]);

  sendRGBCode(rgb);
  delay(1000);

}