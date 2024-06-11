#ifndef WEMOSSERVER_H
#define WEMOSSERVER_H 

#include <ESP8266WiFi.h>
#include <time.h>

using namespace std;

class WemosServer {
public:
    WemosServer();
    ~WemosServer();
    void verbindenWifi();
    void sendMsg(String);
    bool startServer();
    String receivedMsg();

private:

};

#endif
