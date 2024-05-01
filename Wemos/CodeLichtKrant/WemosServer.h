#ifndef WEMOSSERVER_H
#define WEMOSSERVER_H 

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
