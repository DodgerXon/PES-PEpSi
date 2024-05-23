#include <Servo.h>
#include "Server.h"

#define MOTION_SENSOR_PIN D1

WemosServer wServer;
bool isOpen;


void setup() {
  Serial.begin(9600);
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLUP);
  wServer.verbindenWifi();
}

void loop() {
  String command;
  int motionState = digitalRead(MOTION_SENSOR_PIN);
  if(wServer.startServer()){
      command = wServer.receivedMsg();
      Serial.println(command);
      if(command == "status"){
          wServer.sendMsg(String(motionState));
      }
      else{wServer.sendMsg("");}
  }
}
