#include "WemosServer.h"

const int t1 = D1;
const int t2 = D2;
const int t3 = D3;

int buttonStatusT1 = 0;
int buttonStatusT2 = 0;
int buttonStatusT3 = 0;

WemosServer wemos;

void setup() {
    pinMode(t1, INPUT_PULLUP);
    pinMode(t2, INPUT_PULLUP);
    pinMode(t3, INPUT_PULLUP);
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
        // Serial.println("T1 " + buttonStatusT1);
        if (buttonStatusT1 == HIGH) {
            if (wemos.startServer()) {
                wemos.sendMsg("t1");
            }
        }
    } 
    else if (buttonStatusT2 != pinValueT2) {
        buttonStatusT2 = pinValueT2;
        // Serial.println("T2 " + buttonStatusT2);
        if (buttonStatusT2 == HIGH) {
            if (wemos.startServer()) {
                wemos.sendMsg("t2");
            }
        }
    } 
    else if (buttonStatusT3 != pinValueT3) {
        buttonStatusT3 = pinValueT3;
        // Serial.println("T3 " + buttonStatusT3);
        if (buttonStatusT3 == HIGH) {
            if (wemos.startServer()) {
                wemos.sendMsg("t3");
            }
        }
    }
}
