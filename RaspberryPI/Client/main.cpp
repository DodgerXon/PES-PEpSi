#include "Client.h"

int main()
{
	Client client;
		
	while(1)
	{
		client.Connect("145.52.127.190", 8080);
		std::cout << "connected to server" << std::endl;
		
		std::string msg;
		std::getline(std::cin, msg);
		
		client.Send(msg);
		std::cout << "sent: " << msg << std::endl;
		
		std::string receiveText = client.Receive();
		std::cout << "received: " << receiveText << std::endl;
		
		client.Close();
	}
	
	return 0;
}
