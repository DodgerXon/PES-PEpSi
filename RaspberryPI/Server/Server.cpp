#include "Server.h"

Server::Server()
{
	//maak de socket aan.
	if ((listenSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		std::cout << "Can't create socket" << std::endl;
	}
	
	addressLength = sizeof(address);
	
	int opt = 1;
	if(setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cout << "setsockopt error: " << errno << std::endl;
	}
}
	
bool Server::Bind(int port)
{
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	bool status = true;
	if(bind(listenSock, (struct sockaddr*)&address, addressLength) < 0)
	{
		std::cout << "Socket bind error: " << errno << std::endl;
		status = false;
	}
	
	return status;
}

bool Server::Listen()
{
	bool status = true;
    if (listen(listenSock, 3) < 0) 
    {
        std::cout << "Socket listen error: " << errno << std::endl;
		status = false;
    }
    
    return status;
}

bool Server::Accept()
{
	bool status = true;
	if((sock = accept(listenSock, (struct sockaddr*)&address, &addressLength)) < 0)
	{
		std::cout << "Socket accept error: " << errno << std::endl;
		status = false;
	}
	
	return status;
}
