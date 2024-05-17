  
#include "Server.h"

#define PORT 8080

WiFiServer server(PORT);
WiFiClient client;

WemosServer::WemosServer() {}

// char* passwordInput(char* password) {
//     Serial.println("Enter WiFi Password:");
//     while (!Serial.available()) {
//         delay(10);
//     }
//     int i = 0;
//     while (Serial.available()) {
//         password[i] = Serial.read();
//         i++;
//         delay(10);
//     }
//     password[i] = '\0'; // Null-terminate the string
//     return password;
// }

void WemosServer::verbindenWifi() {

  const char* ssid = "NSELab";
  char password[20] = {"NSELab"};

  // Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, "NSELabWiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the ESP8266's IP address
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

}

bool WemosServer::startServer() {
  client = server.available();

    // Check if a client has connected
    if (!client) {
        return false;
    }
    Serial.println("new client");
    return true;
}

String WemosServer::receivedMsg() {
    // Read the request
    String received = client.readStringUntil('\r');
    client.flush();
    return received;
}

