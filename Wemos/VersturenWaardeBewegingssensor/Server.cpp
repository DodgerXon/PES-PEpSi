  
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

    // Start the server    server.begin();
    Serial.println("Server started");


    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

}

bool WemosServer::startServer() {
  client = server.available();
    if (!client) {
        return false;
    }
    return true;
}

String WemosServer::receivedMsg() {
    String received = "";
    char ch;
    
    // Read available bytes
    while (client.available()) {
        ch = client.read();
        if (ch == '\r') {
            break; // Stop reading at the delimiter
        }
        received += ch; // Append character to the result
    }

    client.flush(); // Optional, clears the input buffer

    return received;
}
void WemosServer::sendMsg(String data) {
    if (client.connected()) {
        client.write(data.c_str(), data.length());
        Serial.println("Message sent: " + data);
    } else {
        Serial.println("Error: Client not connected");
    }
}
