#include "Client.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

void updateStatusFile(const std::string& key, const std::string& value) {
    const std::string filePath = "../CLI/status";
    std::vector<std::string> lines = {"rgb", "luchtvochtigheid", "temperatuur", "deur", "lichtkrant", "ventilator"};
    std::ifstream fileIn(filePath);

    if (fileIn.is_open()) {
        std::string line;
        int i = 0;
        while (std::getline(fileIn, line) && i < lines.size()) {
            lines[i++] = line;
        }
        fileIn.close();
    }

    for (std::string& line : lines) {
        if (line.find(key) == 0) {
            line = key + " " + value;
            break;
        }
    }

    std::ofstream fileOut(filePath);
    if (fileOut.is_open()) {
        for (const std::string& line : lines) {
            fileOut << line << std::endl;
        }
        fileOut.close();
    }
}

std::string readStatusFile(const std::string& keyword) {
    const std::string filePath = "../CLI/status";
    std::ifstream fileIn;

    //probeer het bestand in een loop te openen totdat het lukt
    //dit moet omdat meerdere programma's tegelijk bij het bestand moeten
    do
    {
      fileIn.open(filePath);
    } while (!fileIn.is_open());

    std::string line;
    std::string status;

    //ga elke regel in het bestand langs
    while (std::getline(fileIn, line))
    {
        //kijk of het keyword in de regel staat
        size_t keypos = line.find(keyword, 0);

        //als keyword gevonden is verander het status
        if (keypos != -1)
            status =  line.substr(keyword.size()+1);
    }
    
    //sluit bestand
    fileIn.close();

    return status;
}

int main()
{
	Client client;

    std::map<std::string, std::string> components;
    components.emplace("lichtkrant", "145.52.127.244");

    for (const auto& component : components) {
        std::string initialValue = readStatusFile(component.first);
        std::cout << initialValue << std::endl;
        client.Connect(component.second, 8080);
        client.Send(initialValue);
        client.Receive();
        client.Close();
        // todo: check messages sent to server.
    }
    
    while(1) {		
		for (const auto& component : components) {
			client.Connect(component.second, 8080);
			client.Send("status");
			std::string received = client.Receive();
			if(received != readStatusFile(component.first))
			{
				client.Close();
				client.Connect(component.second, 8080);
				client.Send(readStatusFile(component.first));
				client.Receive();
			}
			else 
			{
				updateStatusFile(component.first, received);
			}
			client.Close();
		}		
	}
    return 0;
}
