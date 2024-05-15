#include "Client.h"
#include <sstream>
#include <string>

int main()
{
	Client client;
		
	while(1)
	{
		std::cout << "---------- NEW COMMAND ----------" << std::endl;
		std::cout << "Type 'info' for command information." << std::endl;
		
		std::string input;
		std::getline(std::cin, input);
		
		std::istringstream iss(input);
		std::string token;
		iss >> token;
		
		if(token == "rgb") 
		{
			client.Connect("145.52.127.212", 8080);
			client.Send(input);
			std::cout << "sent: " << input << std::endl;
			client.Close();
		}
		else if(token == "lichtkrant") 
		{
			client.Connect("145.52.127.129", 8080);
			
			std::string message;
			while(iss >> token) 
			{
				message += (token + " ");
			}
			
			client.Send(message);
			std::cout << "sent: " << message << std::endl;
			client.Close();
		}
		else if(token == "info") 
		{
			std::cout << "---------- INFO ----------" << std::endl;
			std::cout << "rgb int int int (Sends RGB values to sfeerverlichting)" << std::endl;
			std::cout << "lichtkrant string (Sends text to lichtkrant)" << std::endl;
		}
		else
		{
			std::cout << "Invalid command. Sending to server." << std::endl;
		}		
		
		std::string receiveText = client.Receive();
	}
	
	return 0;
}
