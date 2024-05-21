#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

void updateStatusFile(const std::string& key, const std::string& value) {
    const std::string filePath = "status";
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

        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string token;
        iss >> token;

        if (token == "rgb")
        {
            updateStatusFile("rgb", input.substr(4));
        }
        else if (token == "lichtkrant")
        {
            updateStatusFile("lichtkrant", input.substr(11));
        }
		else if (token == "ventilator")
        {
            updateStatusFile("ventilator", input.substr(11));
        }
        else if(token == "lichtkrant?") 
        {
			std::cout << readStatusFile("lichtkrant") << std::endl;
		}
		else if(token == "rgb?") 
        {
			std::cout << readStatusFile("rgb") << std::endl;
		}
        else if (token == "info")
        {
            std::cout << "---------- INFO ----------" << std::endl;
            std::cout << "rgb int int int (Sends RGB values to sfeerverlichting)" << std::endl;
            std::cout << "lichtkrant string (Sends text to lichtkrant)" << std::endl;
        }
        else
        {
            std::cout << "Invalid command. Sending to server." << std::endl;
        }
    }
    return 0;
}
