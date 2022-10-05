#pragma once
#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Territory
Territory::Territory(string name) {
    this-> name = name;}

Territory::Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings) {
	this->id = id;
	this->name = name;
	this->x = x;
	this->y = y;
    this->continent_name = continent_name;
    this->neighbours_strings = neighbours_strings;
}

void Territory::add_neighbours(vector <Territory*> neighbours){
    this->neighbours = neighbours;
}

// Continent
Continent::Continent(int id, string name, int score) {
	this->id = id;
	this->name = name;
    this->score = score;
}

// Map
Map::Map(vector<Continent*> continents, map<int, Territory*> territories) {
	this->continents = continents;
	this->territories = territories;
}

Map* MapLoader::loadMap(string filePath) {

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

	map<int, Territory*> territories;
    vector<string> territory_variables;

    // map of names to territories to link neighbours to each territory
	map<string, Territory*> territory_names_to_territories;



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
                std:: cout << endl << "**************************************" << endl; 
                std:: cout << endl << "Parsing Continents..." << endl; 
            }

            // flag parsing territories
            if(line.find("[Territories]") != std::string::npos) {
                parsing_continents = false;
                parsing_territories = true;
                std:: cout << endl << "**************************************" << endl; 
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
                    int index_after_last_delimiter = 0;
                    string territory_name = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter += territory_name.length() + territory_delimiter.length();

                    string x = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter += x.length() + territory_delimiter.length();

                    string y = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter += y.length() + territory_delimiter.length();

                    string continent_name = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter);
                    index_after_last_delimiter += continent_name.length() + territory_delimiter.length();

                    string line_neighbours = line.substr(index_after_last_delimiter); 
                    vector<string> neighbours_strings;
                  
                    std:: cout << endl; 
                    std::cout << "Adding " << territory_name << endl;
                    std::cout << "x: " << x <<", y: " << y <<", continent name: " << continent_name << endl<< "neighbours: ";

                    string neighbour;
                    // while there is a delimeter in the string of neighbours add the territory 
                    while((line_neighbours.find(territory_delimiter) != std::string::npos)){
                        int delimiter_index = line_neighbours.find(territory_delimiter);
                        neighbour = line_neighbours.substr(0, delimiter_index);
                        line_neighbours = line_neighbours.substr(delimiter_index + territory_delimiter.length());
                        neighbours_strings.push_back(neighbour);
                        std::cout << neighbour << " ";
                    }

                    // remove last empty character
                    line_neighbours = line_neighbours.substr(0, line_neighbours.length()-1);
                    
                    // Add last neighbour
                    neighbours_strings.push_back(line_neighbours);
                    std::cout << line_neighbours << endl;

                    // construct territory and add it to list
                    Territory* territory = new Territory(territory_id, territory_name, continent_name, stoi(x), stoi(y), neighbours_strings);
                    // each id maps to a territory pointer

                    territory_names_to_territories.insert(pair<string, Territory*>(territory_name, territory));
                    territories[territory_id] = territory;
                    
                    territory_id++;
                }
            }
        }

        //test map
        // for(pair<string, Territory*> pair : territory_names_to_territories){
        //     std::cout<< pair.first << pair.second->name<<endl;
        // }


        Territory *neighbouring_territory;
        vector<Territory*> neighbours;

        // Iterrate throught the list of territories to add neighbours
        for(pair <int, Territory*> id_and_territory : territories){

            // clear list of neighbours
            neighbours.clear();

            // print territory name
            //std::cout << endl << "name of territory: " << terr->name << endl;

            for(string neighbour_name_string : id_and_territory.second->neighbours_strings){
                // get neighbour territory and add it to list
                neighbouring_territory =  territory_names_to_territories[neighbour_name_string];
                neighbours.push_back(neighbouring_territory);
            }
            
            // add list of its neighbouras to each territory object
            id_and_territory.second->neighbours = neighbours;

            std:: cout << endl << "**************************************" << endl; 
            std::cout<< "Linking neighbours of " << id_and_territory.second->name <<  " (";

            for(Territory *neighbour_in_terr_object : id_and_territory.second->neighbours){
                std::cout << neighbour_in_terr_object->name << " ";
            }
            std:: cout << ")" << endl; 

        }
    }

    // close file
    file.close();

    Map* m = new Map(continents, territories);
    return m;
}