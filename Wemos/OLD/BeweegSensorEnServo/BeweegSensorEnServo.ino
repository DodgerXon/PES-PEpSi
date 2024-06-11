#include <Servo.h>
#include "Server.h"

#define SERVO_PIN D7
#define MOTION_SENSOR_PIN D1

Servo servo;
WemosServer wServer;
bool isOpen;
String command;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLUP);
  servo.write(0);
  wServer.verbindenWifi();
}

void loop() {
  String command;
  if(wServer.startServer()){
      command = wServer.receivedMsg();
  }
  int motionState = digitalRead(MOTION_SENSOR_PIN);
  //String command = Serial.readStringUntil('\n');

  if(command == "open "){ 
    isOpen = true;
  }
  else if(command == "sluit "){
    isOpen = false;
  }
  
  if(isOpen == true){
    servo.write(180);
  }else if(isOpen == false){
    if (motionState == HIGH) {
      servo.write(180); // Draai de servo naar de open positie als er beweging is gedetecteerd en de servo gesloten is
    } else if (motionState == LOW) {
      servo.write(0); // Draai de servo naar de gesloten positie als er geen beweging is gedetecteerd en de servo open is
    }
  }
}