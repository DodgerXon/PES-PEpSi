#include "WemosServer.h"

const int t1 = D1;
const int t2 = D2;
const int t3 = D3;

const int boardLed = 2; // D4

int buttonStatusT1 = 0;
int buttonStatusT2 = 0;
int buttonStatusT3 = 0;

WemosServer wemos;

void setup() {
    pinMode(t1, INPUT_PULLUP);
    pinMode(t2, INPUT_PULLUP);
    pinMode(t3, INPUT_PULLUP);

    pinMode(boardLed, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
    digitalWrite(boardLed, LOW);

    Serial.begin(9600);
    wemos.verbindenWifi();
}

void loop() {
    int pinValueT1 = digitalRead(t1);
    int pinValueT2 = digitalRead(t2);
    int pinValueT3 = digitalRead(t3);

    delay(10);
    if (buttonStatusT1 != pinValueT1) {
        buttonStatusT1 = pinValueT1;
        if (buttonStatusT1 == HIGH) {
            Serial.print("T1 ");
            if (wemos.startServer()) {
                wemos.sendMsg("t1");
            }
        }
    } else if (buttonStatusT2 != pinValueT2) {
        buttonStatusT2 = pinValueT2;
        if (buttonStatusT2 == HIGH) {
            Serial.print("T2 ");
            if (wemos.startServer()) {
                wemos.sendMsg("t2");
            }
        }
    } else if (buttonStatusT3 != pinValueT3) {
        buttonStatusT3 = pinValueT3;
        if (buttonStatusT3 == HIGH) {
            Serial.print("T3 ");
            if (wemos.startServer()) {
                wemos.sendMsg("t3");
            }
        }
    }
}
