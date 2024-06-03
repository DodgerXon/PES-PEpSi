#include "Client.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

void updateStatusFile(const std::string& key, const std::string& value) {
    const std::string filePath = "../CLI/status";
    std::vector<std::string> lines = {"deur", "rgb", "lichtkrant", "beweging1", "beweging2", "t1", "temperatuur", "luchtvochtigheid", "ventilator", "l1", "co2"};
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
    components.emplace("lichtkrant", "145.52.127.209");
    components.emplace("beweging1", "145.52.127.210");
    components.emplace("rgb", "145.52.127.207");
    components.emplace("deur", "145.52.127.242");
    components.emplace("beweging2", "145.52.127.199");
    components.emplace("t1", "145.52.127.198");
    components.emplace("temperatuur", "145.52.127.190");
    components.emplace("luchtvochtigheid", "145.52.127.190");
    components.emplace("co2", "145.52.127.190");
    components.emplace("ventilator", "145.52.127.190");
    components.emplace("l1", "145.52.127.190");

    for (const auto& component : components) 
    {
        std::string initialValue = readStatusFile(component.first);
        std::cout << initialValue << std::endl;
        
        client.Connect(component.second, 8080);
        
        client.Send(initialValue);
        client.Receive();
        
        client.Close();
        // todo: check messages sent to server.
    }
    
    while(1) 
    {		
		for (const auto& component : components) 
        {
            std::string name = component.first;
            //als component zit aan server pi
            if(component.second == "145.52.127.190")
            {
                if(name == "l1")
                {
                    updateStatusFile(name, readStatusFile("t1"));
                    
                    client.Connect(components["l1"], 8080);
                    client.Send("l1 " + readStatusFile(component.first));
                    std::string received = client.Receive();
                    client.Close();
                }
                
                if(name == "temperatuur") {
                    client.Connect(components["temperatuur"], 8080);
                    client.Send("temperatuur");
                    updateStatusFile(component.first, client.Receive());
                    client.Close();
                    
                    float temp = std::stof(readStatusFile(component.first));
                    if(temp > 30.0f)
                    {
                        client.Connect(component.second, 8080);
                        client.Send("ventilator true");
                        std::string received = client.Receive();
                        client.Close();
                    }
                }
                    
                else if(name == "luchtvochtigheid") {
                    client.Connect(components["luchtvochtigheid"], 8080);
                    client.Send("luchtvochtigheid");
                    updateStatusFile(component.first, client.Receive());
                    client.Close();
                }
                    
                else if(name == "ventilator") {
                    client.Connect(component.second, 8080);
                    client.Send("ventilator status");
                    std::string received = client.Receive();
                    client.Close();
                    
                    if(received != readStatusFile(component.first)) 
                    {
                        client.Connect(components["ventilator"], 8080);
                        client.Send("ventilator " + readStatusFile(component.first));
                        client.Receive();
                        client.Close();
                    }
                }

                else if(name == "co2") {
                    client.Connect(components["co2"], 8080);
                    client.Send("co2");
                    updateStatusFile(component.first, client.Receive());
                    client.Close();
                }
            }
            //als component zit aan client pi
            else
            {
            	client.Connect(component.second, 8080);
                client.Send("status");
                std::string received = client.Receive();
                client.Close();
                       
                if(received != readStatusFile(component.first))
                {
    
                    //als het een actuator is is het bestand door de CLI aangepast
                    //hetgene wat in het bestand staat moet dan verstuurd worden naar de server
                    if(name == "rgb" ||
                        name == "deur" ||
                        name == "lichtkrant" ||
                        name == "t1")
                    {
                        if(name == "rgb") {
                            if(readStatusFile("beweging1") == "Aan")
                            {
                                client.Connect(components["rgb"], 8080);
                                client.Send("Aan");
                                client.Receive();
                                client.Close();
                            }
                        }
                        
                        if(name == "deur")
                        {
                            if(readStatusFile("beweging2") == "Aan")
                            {
                                client.Connect(components["deur"], 8080);
                                client.Send("open");
                                client.Receive();
                                client.Close();
                            }
                        }      
                        
                        if(name == "t1")
                        {
                            std::cout << "received van wemos : " << received << std::endl;
                            std::cout << "bestand: " << readStatusFile(component.first) << std::endl;

                            client.Connect(component.second, 8080);
                            client.Send(readStatusFile(component.first));
                            client.Receive();
                            client.Close();
                            
                            client.Connect(component.second, 8080);
                            client.Send("status");
                            std::string newReceived = client.Receive();
                            client.Close();
                        
                            std::cout << "new received van wemos : " << newReceived << std::endl;
                        
                            updateStatusFile("t1", newReceived);
                            
                            std::cout << "new bestand: " << readStatusFile(component.first) << std::endl << std::endl;
                            
                        }
                        
                        client.Connect(component.second, 8080);
                        client.Send(readStatusFile(component.first));
                        client.Receive();
                        client.Close();
                    }
                    //als het een sensor is dan wil je juist de waarde aanpassen in het bestand
                    else
                    {
                        updateStatusFile(component.first, received);
                    }
                }
            }
		}	
	}
    return 0;
}
