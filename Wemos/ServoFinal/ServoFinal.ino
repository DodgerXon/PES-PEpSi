#include <Servo.h>
#include "Server.h"
#include "Deur.h"

WemosServer wServer;
String command;
Deur deurtje;

unsigned long previousMillis = 0;
const long interval = 10000;  // Interval in milliseconds


void setup() {
  Serial.begin(9600);
  wServer.verbindenWifi();
  deurtje.deurSluit();
}

void loop() {
  String opdracht;

  if(wServer.startServer()){
    opdracht = wServer.receivedMsg(); // leest binnengekomen bericht
    if(opdracht == "status"){
      String status = deurtje.deurStatus(); // stuurt de status van de deur.
      wServer.sendMsg(status);
    }
    else if(opdracht == "open"){
    deurtje.deurOpen(); // als er open is gestuurd gaat de servo open
    } else {
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis >= interval){ // na 10 sec gaat de deur weer sluiten
        deurtje.deurSluit();
          previousMillis = currentMillis;
      }
    }
  }
}