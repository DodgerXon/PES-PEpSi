#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "WemosServer.h"

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

const int DATA_PIN = D8; // DIN
const int CLK_PIN = D5; // CLK
const int CS_PIN = D7; // CS
char buf[100] = "Nog geen tekst";

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
  if (wServer.startServer()) {
    String received = wServer.receivedMsg();
    if (received == "status") {
      wServer.sendMsg(String(buf));
    } else {
      received.toCharArray(buf, received.length() + 1); // Include space for the null terminator
      wServer.sendMsg(received);
    }
  }
// Tekent de 'buf' op de lichtkrant. Dit blijft non stop doorloopen.
  if (P.displayAnimate()) {
    P.displayText(buf, PA_LEFT, 30, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}
