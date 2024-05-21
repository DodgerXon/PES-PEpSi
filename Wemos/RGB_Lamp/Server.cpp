#include "Server.h"

#define PORT 8080

WiFiServer server(PORT);
WiFiClient client;

WemosServer::WemosServer() {
}
WemosServer::~WemosServer() {}

char* passwordInput(char* password) {
    Serial.println("Enter WiFi Password:");
    while (!Serial.available()) {
        delay(10);
    }
    int i = 0;
    while (Serial.available()) {
        password[i] = Serial.read();
        i++;
        delay(10);
    }
    password[i] = '\0'; // Null-terminate the string
    return password;
}

void WemosServer::verbindenWifi() {

  IPAddress local_IP(145, 52, 127, 207);
  IPAddress gateway(145, 52, 127, 1);   // Change to your network's gateway
  IPAddress subnet(255, 255, 255, 0);   // Change to your network's subnet mask

  const char* ssid = "NSELab";
  char password[20] = {""};

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(local_IP, gateway, subnet); // Zet een vast IP adres.
  WiFi.begin(ssid, passwordInput(password));

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

void WemosServer::startServer() {

  client = server.available();

    // Check if a client has connected
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
        delay(1);
    }
}

String WemosServer::receivedMsg() {

    // Read the request
    String received = "";
    if (client.available()) {
        received = client.readStringUntil('\r');
    } else {
        return "";
    }

  //Serial.print("Server:"); Serial.println(received);

  client.flush();
  return received;
}