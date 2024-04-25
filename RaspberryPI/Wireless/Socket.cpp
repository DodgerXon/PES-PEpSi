#include "Socket.h"

void Socket::Close()
{
	//sluit de socket af.	
	close(sock);
}

void Socket::Send(std::string msg)
{
	//verzend de data in de string.
	send(sock, msg.c_str(), msg.length(), 0);
}

std::string Socket::Receive()
{
	//zet de binnengekomen data in een buffer.
	//LET OP, als er meer dan 1024 bytes verstuurd worden is dit een buffer overflow
	char buffer[1024];
	read(sock, buffer, 1024 - 1);
	
	//zet de buffer data in een string.
	std::string received(buffer);
	
	return received;
}

