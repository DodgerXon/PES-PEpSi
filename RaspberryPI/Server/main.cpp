#include "Server.h"
#include "i2c_com.h"

int main() {
    Server server;
    server.Bind(8080);
    I2C_COM i2c;
    
    //oneindige loop
    while (true) {
        //wacht op nieuwe client connection
        server.Listen();
        server.Accept() 
        
        std::cout << "Client connected" << std::endl;
        
        //sla bericht van client op in receivedText
        std::string receiveText = server.Receive();
        std::cout << "Received: " << receiveText << std::endl;
        
        std::string messageToClient;
        
        //bepaal wat terug naar de client gestuurd moet worden
        if (receiveText == "temp") {
            messageToClient = i2c.requestDataFromSlave(0x10, 0x01);
        } else if (receiveText == "hum") {
            messageToClient = i2c.requestDataFromSlave(0x10, 0x02);
        } else if (receiveText == "open") {
            i2c.requestDataFromSlave(0x20, 0x03);
            messageToClient = "Opened";
        } else if (receiveText == "closed") {
            i2c.requestDataFromSlave(0x20, 0x04);
            messageToClient = "Closed";
        } else {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        
        //stuur data terug naar client
        server.Send(messageToClient);
        std::cout << "Sent: " << messageToClient << std::endl;
    }
    
    server.Close(); // Close the server socket
    return 0;
}
