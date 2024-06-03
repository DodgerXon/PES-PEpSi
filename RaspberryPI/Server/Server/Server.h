#include "Socket.h"

class Server : public Socket
{
private:
	int listenSock;
	struct sockaddr_in address;
	socklen_t addressLength;
	
public:
	Server();
	
	bool Bind(int);
	bool Listen();
	bool Accept();
	void CloseClient();
};
