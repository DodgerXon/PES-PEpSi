#include "WemosServer.h"

const int t1 = D1; //Pin voor knop T1

const int boardLed = 2; // Pin voor de ingebouwde led (D4)

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

    int pinValueT1 = digitalRead(t1); //Lees waarde van button 1

    if (wServer.startServer()) {

      String received = wServer.receivedMsg(); //Ontvangen bericht van de server

      if (received == "uit") {
        buttonPressed = false;
        Serial.println("Button uit");
      }
      else
      {
        if (buttonPressed) 
        {
          wServer.sendMsg("aan"); //Verstuurt 'aan' als op de knop gedrukt is.
        } 
        else 
        {
          wServer.sendMsg("uit");
        }
      }


    }

    if (buttonStatusT1 != pinValueT1) { //Controleert of de status van de knop is veranderd.
        buttonStatusT1 = pinValueT1; // Update de knop status
        if (buttonStatusT1 == HIGH) { 
            buttonPressed = true; //Zet variable op true.
            Serial.println("T1 ");
        }
    } 
}
