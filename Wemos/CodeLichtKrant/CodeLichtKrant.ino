// Program to demonstrate the MD_Parola library
//
// Simplest program that does something useful - Hello World!
//
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "WemosServer.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

const int DATA_PIN = D8; // DIN
const int CLK_PIN = D5; // CLK
const int CS_PIN = D7; // CS
char buf[20] = {"Nog geen tekst"};

WemosServer wServer;

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
void setup(void)
{
  Serial.begin(9600);
  delay(10);
  P.begin();
  wServer.verbindenWifi();
}

void loop(void)
{
  if(wServer.startServer()) {
    String received = wServer.receivedMsg();
    received.toCharArray(buf, received.length());
    buf[received.length()] = '\0';
  }

  if (P.displayAnimate()) {
    P.displayText(buf, PA_LEFT, 30, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT); // Use the character array
  }
}

