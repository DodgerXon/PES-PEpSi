#include "Server.h"

int main()
{
	Server server;
	server.Bind(8080);
		
	while(1)
	{
		server.Listen();
		server.Accept(); //Todo: geef return waarde
		std::cout << "client connected" << std::endl;
		
		std::string receiveText = server.Receive();
		std::cout << "received: " << receiveText << std::endl;
		
		std::string sendText = "hello world!";
		server.Send(sendText);
		std::cout << "sent: " << sendText << std::endl;
		
		server.Close();
	}
	
	return 0;
}
