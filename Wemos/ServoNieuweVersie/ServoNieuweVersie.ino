#include <Servo.h>
#include "WemosServer.h"

#define SERVO_PIN D7

Servo servo;
WemosServer wServer;
bool isOpen;
String command;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(0);
  wServer.verbindenWifi();
}

void loop() {
  String command;
  String deStatus = "";
  if(wServer.startServer()){
    command = wServer.receivedMsg();
    Serial.println(command);
    if(command == "status"){
      wServer.sendMsg(deStatus);
    }
    else if(command == "open"){ 
        servo.write(180);
        deStatus = "open";
    }
    else if(command == "sluit"){
        servo.write(0);
        deStatus = "sluit";
    }
  }
}