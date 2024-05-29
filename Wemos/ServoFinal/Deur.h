#ifndef DEUR_H
#define DEUR_H
#include <Servo.h>
using namespace std;

class Deur{
public:
Deur();
~Deur();
void deurOpen();
void deurSluit();
String deurStatus();

private:
String status;
Servo servo;
};

#endif