#ifndef SERVER_H
#define SERVER_H 

#include <ESP8266WiFi.h>

using namespace std;

class WemosServer {
public:
    WemosServer();
    void verbindenWifi();
    void sendMsg(String);
    bool startServer();
    String receivedMsg();
};

#endif