#include "Socket.h"

class Client : public Socket
{
private:
	struct sockaddr_in serverAddress;
	socklen_t serverAddressLength;
	
public:
	Client();
	
	bool Connect(std::string, int);
};
