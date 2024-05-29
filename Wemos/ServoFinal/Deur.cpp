#include "Deur.h"
using namespace std;
#define SERVO_PIN D7

Deur::Deur():status("dicht"){
    servo.attach(SERVO_PIN);
}

Deur::~Deur(){}


void Deur::deurOpen(){
  status = "open";
  servo.write(180);
}

void Deur::deurSluit(){
  status = "dicht";
  servo.write(0);
}

String Deur::deurStatus(){
  return status;
}