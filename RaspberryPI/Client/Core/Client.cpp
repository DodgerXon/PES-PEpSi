#include "Client.h"

Client::Client()
{
	//lengte van serverAddress opslaan, 
	//hebben we later nodig in bepaalde functies
	serverAddressLength = sizeof(serverAddress);
}

bool Client::Connect(std::string ip, int port)
{
	//elke keer als een socket geclosed is moet je een nieuwe openen
	//dus elke keer dat je met server wil verbinden, open je een socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		std::cout << "Can't create socket" << std::endl;
	}
	
	//in serv_adr wordt data over de server opgeslagen zoals ...
	//het port nummer van de server.
	serverAddress.sin_port = htons(port);

	//het IP adres van de server,
	//met de onderstaande functie wordt het IP gecoverteerd naar binary form.
	if (inet_pton(AF_INET, ip.c_str(), &serverAddress.sin_addr) <= 0) 
	{
		std::cout << "Invalid IP address / address not supported" << std::endl;
	}

	//dat het verbinden met de server gaat via internet.
	serverAddress.sin_family = AF_INET;

	//dan wordt geprobeert om vanaf de socket verbinding te maken met de server.
	bool status = true;
	if ((connect(sock, (struct sockaddr*)&serverAddress, serverAddressLength)) < 0) 
	{
		std::cout << "Connection Failed" << std::endl;
		status = false;
	}
	
	return status;
}
