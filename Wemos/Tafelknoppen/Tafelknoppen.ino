#include "WemosServer.h"

const int t1 = D1;

const int boardLed = 2; // D4

int buttonStatusT1 = 0;

bool buttonPressed = false;

WemosServer wServer;

void setup() {
    pinMode(t1, INPUT_PULLUP);

    pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
    digitalWrite(boardLed, LOW);

    Serial.begin(9600);
    wServer.verbindenWifi();
}

void loop() {

    int pinValueT1 = digitalRead(t1);

    if (wServer.startServer()) {

      String received = wServer.receivedMsg();

      if (received == "uit") {
        buttonPressed = false;
        Serial.println("Button uit");
      }
      else
      {
        if (buttonPressed) 
        {
          wServer.sendMsg("aan");
        } 
        else 
        {
          wServer.sendMsg("uit");
        }
      }


    }

    if (buttonStatusT1 != pinValueT1) {
        buttonStatusT1 = pinValueT1;
        if (buttonStatusT1 == HIGH) {
            buttonPressed = true;
            Serial.println("T1 ");
        }
    } 
}
