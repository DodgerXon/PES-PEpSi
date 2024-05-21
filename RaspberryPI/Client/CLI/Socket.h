#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

class Socket
{
protected:
	int sock;
	
public:
	virtual ~Socket() = default;
	
	void Close();
	
	void Send(std::string);
	std::string Receive();
};
