#ifndef SERVER_H
#define SERVER_H 

#include <ESP8266WiFi.h>

using namespace std;

class WemosServer {
public:
    WemosServer();
    //~WemosServer();
    void verbindenWifi();
    void startServer();
    String receivedMsg();

private:

};

#endif
