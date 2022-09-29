#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Territory
Territory::Territory(int id, string name, int x, int y, int continent_id) {
	this->id = id;
	this->name = name;
	this->x = x;
	this->y = y;
    this->continent_id = continent_id;
}

// Continent
Continent::Continent(int id, string name, int score) {
	this->id = id;
	this->name = name;
    this->score = score;
}

// Map
Map::Map(vector<Continent*> continents, vector<Territory*> territories) {
	this->continents = continents;
	this->territories = territories;
}

Map* MapLoader::loadMap(string filePath) {

	// Open the file
	ifstream file(filePath);
	string line;
	string territory_delimiter = ",";
    string continent_delimiter = "=";
    int delimiter_index = 0;
	int continent_id = 0;
    int territory_id = 0;

    bool parsing_continents = false;
    bool parsing_territories = false;

	vector<Continent*> continents; 
    vector<string> continent_variables;

	vector<Territory*> territories;
    vector<string> territory_variables;

    // file does not exist
    if(!file){
        std::cout << filePath << " does not exist."<< endl;
    }

    // file exists
    else{
        std::cout << filePath <<  " exist."<< endl;
        
        // read each line while it exists
        while (std::getline(file, line)) {

            // flag parsing continent
            if(line.find("[Continents]") != std::string::npos) {
                parsing_continents = true;
                std:: cout << endl << "Parsing Continents..." << endl; 
            }

            // flag parsing territories
            if(line.find("[Territories]") != std::string::npos) {
                parsing_continents = false;
                parsing_territories = true;
                std:: cout << endl  << "Parsing Territories..." << endl; 
            }

            // Parse continents
            if (parsing_continents && !(line.find("[Continents]") != std::string::npos)) {                

                if (!(line.find(continent_delimiter) != std::string::npos)) { // skip line if does not have the continent delimiter
                    std::cout << endl  << "Territiries section finished ..." << endl;
                    continue;
                }
                
                else {
                    // Get continent fields
                    string continent_name = line.substr(0, line.find(continent_delimiter));
                    int index_after_last_delimiter = continent_name.length() + continent_delimiter.length();

                    string score = line.substr(index_after_last_delimiter, line.find(continent_delimiter, index_after_last_delimiter));
                    
                    Continent* c = new Continent(continent_id, continent_name, stoi(score));
                    continents.push_back(c);
                    std::cout << "Adding " << continent_name << endl;
                    continent_id++;
                }
            }

            // Parse territories
            else if (parsing_territories && !(line.find("[Territories]") != std::string::npos)) {                
                
                if (!(line.find(territory_delimiter) != std::string::npos)) { // skip line if does not have the territory delimiter
                    std::cout << endl  << "Territiries section finished ..." << endl;
                    continue;
                }

                else {
                    int offset = 0;
                    string territory_name = line.substr(offset, line.find(territory_delimiter, offset) - offset); // Name
                    offset += territory_name.length() + territory_delimiter.length();

                    string x = line.substr(offset, line.find(territory_delimiter, offset) - offset); // X position
                    offset += x.length() + territory_delimiter.length();

                    string y = line.substr(offset, line.find(territory_delimiter, offset) - offset); // Y position

                    string continent = line.substr(offset, line.find(territory_delimiter, offset) - offset); // Continent that it's on
                    offset += continent.length() + territory_delimiter.length();

                    Territory* t = new Territory(territory_id, territory_name, stoi(continent), stoi(x), stoi(y));
                    territories.push_back(t);
                    territory_id++;
                    std::cout << "Adding " << territory_name << endl;
                }
            }
        }
    }

    // close file
    file.close();

    Map* m = new Map(continents, territories);
    return m;
}