  
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

  IPAddress local_IP(10, 42, 0, 11);
  IPAddress gateway(0, 0, 0, 0);   // Change to your network's gateway
  IPAddress subnet(255, 255, 255, 0);   // Change to your network's subnet mask

  const char* ssid = "pepsi_wifi";
  char password[20] = {"pepsi123"};

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(local_IP, gateway, subnet); // Zet een vast IP adres.
  //WiFi.begin(ssid, passwordInput(password));
  WiFi.begin(ssid, "pepsi123");

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

