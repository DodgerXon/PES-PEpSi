#include "Server.h"
#include "i2c_com.h"

int main() {
    Server server;
    if (!server.Bind(8080)) {
        std::cerr << "Failed to bind to port 8080" << std::endl;
        return -1;
    }

    I2C_COM i2c;

    while (true) {
        if (!server.Listen()) {
            std::cerr << "Listen failed" << std::endl;
            continue; // Retry listening
        }

        if (server.Accept()) {
            std::cout << "Client connected" << std::endl;

            std::string receiveText = server.Receive();
            std::cout << "Received: " << receiveText << std::endl;

            std::string messageToClient;

            if (receiveText == "temperatuur") 
            {
                messageToClient = i2c.requestDataFromSlave(0x10, 0x01);
            } 
            else if (receiveText == "luchtvochtigheid") 
            {
                messageToClient = i2c.requestDataFromSlave(0x10, 0x02);
            }
            else if (receiveText == "co2") 
            {
                messageToClient = i2c.requestDataFromSlave(0x20, 0x01);
            } 
            else if (receiveText == "ventilator status")
            {
                std::string a = i2c.requestDataFromSlave(0x11, 0x03);
                
                if (a == "0")
                    receiveText = "false";
                else if(a == "1")
                    receiveText = "true";
            }
            else if (receiveText == "ventilator true")
            {
                i2c.requestDataFromSlave(0x11, 0x01);
                receiveText = " ";
            }
            else if (receiveText == "ventilator false")
            {
                i2c.requestDataFromSlave(0x11, 0x02);
                receiveText = " ";
            }
            else if (receiveText == "l1 aan")
            {
                i2c.requestDataFromSlave(0x21, 0x01);
                receiveText = " ";
             }
            else if (receiveText == "l1 uit")
            {
                i2c.requestDataFromSlave(0x21, 0x02);
                receiveText = " ";
            }
            else 
            {
                //std::cout << "Verkregen bericht: " <<receiveText <<std::endl;
                messageToClient = "Invalid input";
                std::cout << "Invalid input" << std::endl;
            }

            server.Send(messageToClient);
            std::cout << "Sent: " << messageToClient << "\n"<< std::endl;

            // Close client connection after processing
            server.CloseClient();
        } else {
            std::cerr << "Failed to accept client connection" << std::endl;
        }
    }

    return 0;
}
