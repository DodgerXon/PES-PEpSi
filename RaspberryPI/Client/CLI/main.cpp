#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

//todo: StatusFile class aanmaken in plaats van deze losse functies

void updateStatusFile(const std::string& key, const std::string& value) {
    const std::string filePath = "status";
    std::vector<std::string> lines = {"deur", "rgb", "lichtkrant", "beweging1", "beweging2", "t1", "temperatuur", "luchtvochtigheid", "ventilator", "l1", "co2"};
    std::ifstream fileIn(filePath); //open het statusfile voor reading

    //als hij geopent is
    if (fileIn.is_open()) 
    {
        std::string line;
        int i = 0;

        //loop door alle lines in het bestand heen en zet de regels in de lines vector 
        //dit doen we zodat de huidige data bestand hetzelfde blijft
        while (std::getline(fileIn, line) && i < lines.size()) 
        {
            lines[i++] = line;
        }
        
        //sluit bestand
        fileIn.close();
    }

    //loop door alle regels
    for (std::string& line : lines) 
    {
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

        //close de file
        fileOut.close();
    }
}

std::string readStatusFile(const std::string& keyword) {
    const std::string filePath = "status";
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
    while (1)
    {
        std::cout << "---------- NEW COMMAND ----------" << std::endl;
        std::cout << "Type 'info' for command information." << std::endl;

        //pak gebruiker input
        std::string input;
        std::getline(std::cin, input);

        //pak eerste woord uit input en zet het in key
        std::istringstream iss(input);
        std::string key;
        iss >> key;

        //check met key welk command is ingevoerd  
        if (key == "rgb")
        {
            updateStatusFile("rgb", input.substr(4));
        }
        else if (key == "lichtkrant")
        {
            updateStatusFile("lichtkrant", input.substr(11));
        }
        else if(key == "deur")
        {
            updateStatusFile("deur", input.substr(5));
        }
        else if(key == "ventilator")
        {
            updateStatusFile("ventilator", input.substr(11));
        }
        else if(key=="t1")
        {
            updateStatusFile("t1", input.substr(3));
        }
        else if(key == "bewegingrgb?")
        {
            std::cout << readStatusFile("beweging1") << std::endl;
        }
        else if(key == "bewegingdeur?")
        {
            std::cout << readStatusFile("beweging2") << std::endl;
        }
		else if(key == "rgb?") 
        {
			std::cout << readStatusFile("rgb") << std::endl;
		}
        else if(key == "lichtkrant?") 
        {
			std::cout << readStatusFile("lichtkrant") << std::endl;
		}
        else if(key == "temperatuur?") 
        {
			std::cout << readStatusFile("temperatuur") << std::endl;
		}
        else if(key == "luchtvochtigheid?") 
        {
			std::cout << readStatusFile("luchtvochtigheid") << std::endl;
		}
        else if(key == "co2?") 
        {
			std::cout << readStatusFile("co2") << std::endl;
		}
        else if(key == "ventilator?") 
        {
			std::cout << readStatusFile("ventilator") << std::endl;
		}
        else if(key == "t1?") 
        {
			std::cout << readStatusFile("t1") << std::endl;
		}
        else if(key == "l1?") 
        {
			std::cout << readStatusFile("l1") << std::endl;
		}
        else if (key == "info")
        {
            std::cout << "---------- ZET DATA ----------" << std::endl;
            std::cout << "rgb int int int - Zet de RGB verlichting (waarde 0 tot 255)" << std::endl;
            std::cout << "lichtkrant string - Zet de RGB verlichting (lengte tekst tot 20 karakters)" << std::endl;
            std::cout << "deur string - Open of sluit de deur (waarde open of dicht)" << std::endl;
            std::cout << "ventilator bool - Zet de ventilator aan of uit (waarde true of false)" << std::endl;
            std::cout << "t1 bool - Zet de tafelknop uit (waarde true of false)" << std::endl;
            std::cout << "---------- VRAAG DATA ----------" << std::endl;
            std::cout << "lichtkrant? - Geeft de waarde van de lichtkrant terug" << std::endl;
            std::cout << "rgb? - Geeft waarde de van de RGB verlichting terug" << std::endl;
            std::cout << "bewegingrgb? - Geeft de waarde van de lamp sensor terug" << std::endl;
            std::cout << "bewegingdeur? - Geeft de waarde van de deur sensor terug" << std::endl;
            std::cout << "t1? - Geeft de waarde van tafel 1 bestelknop terug" << std::endl;
            std::cout << "temperatuur? - Geeft de waarde van de temperatuur terug" << std::endl;
            std::cout << "luchtvochtigheid? - Geeft de waarde van de luchtvochtigheid terug" << std::endl;
            std::cout << "co2? - Geeft de waarde van het co2 gehalte terug" << std::endl;
            std::cout << "ventilator? - Geeft de waarde van de ventilator terug" << std::endl;
            std::cout << "l1? - Geeft de waarde van de lamp gekoppeld aan tafel 1 terug" << std::endl;
           
        }
        else
        {
            std::cout << "Invalid command..." << std::endl;
        }
    }
    
    return 0;
}
