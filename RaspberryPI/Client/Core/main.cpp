#include "Client.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

//todo: StatusFile class aanmaken in plaats van deze losse functies
void updateStatusFile(const std::string& key, const std::string& value) {
    const std::string filePath = "../CLI/status";
    std::vector<std::string> lines = {"deur", "rgb", "lichtkrant", "beweging1", "beweging2", "t1", "temperatuur", "luchtvochtigheid", "ventilator", "l1", "co2"};
    std::ifstream fileIn(filePath);//open het statusfile voor reading

    //als hij geopent is
    if (fileIn.is_open()) {
        std::string line;
        int i = 0;
        
        //loop door alle lines in het bestand heen en zet de regels in de lines vector 
        //dit doen we zodat de huidige data bestand hetzelfde blijft
        while (std::getline(fileIn, line) && i < lines.size()) {
            lines[i++] = line;
        }

        //sluit bestand
        fileIn.close();
    }

    //loop door alle regels
    for (std::string& line : lines) {
        //als de key op die regel staat zet de nieuwe waarde in de lines vector
        if (line.find(key) == 0) {
            line = key + " " + value;
            break;
        }
    }

    //open de statusfile voor writing
    std::ofstream fileOut(filePath);
    //als hij geopent is
    if (fileOut.is_open()) {

        //zet elke line van de vector in de file
        for (const std::string& line : lines) {
            fileOut << line << std::endl;
        }

        //sluit bestand
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


//todo: component logic duidelijker neerzetten, er staan onnodige if statements
int main()
{
	Client client;

    //zet alle componenten in een map
    std::map<std::string, std::string> components;
    components.emplace("beweging1", "10.42.0.10");
    components.emplace("lichtkrant", "10.42.0.11");
    components.emplace("rgb", "10.42.0.12");
    components.emplace("deur", "10.42.0.13");
    components.emplace("beweging2", "10.42.0.14");
    components.emplace("t1", "10.42.0.15");
    components.emplace("temperatuur", "10.42.0.16");
    components.emplace("luchtvochtigheid", "10.42.0.16");
    components.emplace("co2", "10.42.0.16");
    components.emplace("ventilator", "10.42.0.16");
    components.emplace("l1", "10.42.0.16");

    //loop door de componenten heen
    for (const auto& component : components) 
    {
        //pak status die in het bestand staat
        std::string initialValue = readStatusFile(component.first);
        std::cout << initialValue << std::endl;
        
        //stuur status uit het bestand naar componenten, 
        //dit is zodat de actuatoren gelijk naar de goede status gaan  
        client.Connect(component.second, 8080);
        client.Send(initialValue);
        client.Receive();
        client.Close();
    }
    
    //oneindige loop
    while(1) 
    {		
        //loop door de componenten heen
		for (const auto& component : components) 
        {
            //pak het naam van het huidige component
            std::string name = component.first;


            //als het component zit aan server pi
            if(component.second == "10.42.0.16")
            {
                //bestel lamp 
                if(name == "l1")
                {
                    updateStatusFile(name, readStatusFile("t1"));
                    
                    client.Connect(components["l1"], 8080);
                    client.Send("l1 " + readStatusFile(component.first));
                    std::string received = client.Receive();
                    client.Close();
                }
                
                //temp sensor
                if(name == "temperatuur") {
                    client.Connect(components["temperatuur"], 8080);
                    client.Send("temperatuur");
                    updateStatusFile(component.first, client.Receive());
                    client.Close();
                    
                    float temp = std::stof(readStatusFile(component.first));
                    if(temp > 26.0f)
                    {
                        client.Connect(component.second, 8080);
                        client.Send("ventilator true");
                        std::string received = client.Receive();
                        client.Close();
                    }
                }
                    
                //luchtvochtigheid sensor
                else if(name == "luchtvochtigheid") {
                    client.Connect(components["luchtvochtigheid"], 8080);
                    client.Send("luchtvochtigheid");
                    updateStatusFile(component.first, client.Receive());
                    client.Close();
                }
                
                //ventilator
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

                //co2 sensor
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
                //vraag eerst de status op en sla op in received
            	client.Connect(component.second, 8080);
                client.Send("status");
                std::string received = client.Receive();
                client.Close();
                       
                //als het ontvangen status anders is dan de status file moet er iets worden gedaan
                if(received != readStatusFile(component.first))
                {
                    //als het een actuator is is het bestand door de CLI aangepast
                    //hetgene wat in het bestand staat moet dan verstuurd worden naar de server
                    if(name == "rgb" ||
                        name == "deur" ||
                        name == "lichtkrant" ||
                        name == "t1")
                    {
                        //stuur status naar rgb
                        if(name == "rgb") {
                            if(readStatusFile("beweging1") == "Aan")
                            {
                                client.Connect(components["rgb"], 8080);
                                client.Send("Aan");
                                client.Receive();
                                client.Close();
                            }
                        }

                        //stuur status naar deur
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
                        
                        //stuur status naar de tafel knop
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
                        
                        //stuur de nieuwe status naar het component
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
