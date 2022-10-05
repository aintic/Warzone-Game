#pragma once
#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <set>

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

ostream& operator <<(ostream& stream, const Territory& t){
    return stream << " ..."<< t.name << endl;
}

// Continent
Continent::Continent(int id, string name, int score) {
	this->id = id;
	this->name = name;
    this->score = score;
}

// Map
Map::Map(map<int, Continent*> continents, map<int, Territory*> territories) {
	this->continents = continents;
	this->territories = territories;
}

// validate method
void Map::validate(){

    std::cout<< "Starting validation:"<< endl;
    // (1) Map is connected subgraph
    
    // To confirm that the map is a connected graph we start with the first territory in 
    // the map and visit each of it's territories in a DFS-like manner. we keep a count of 
    // visited territories and if the count of all visited territories corresponds to the 
    // number of territories in the map, the graph is indeed connected.
    Territory* current_territory = this->territories.begin()->second; // take first territory in map
    stack<Territory*> next_territories;
    set<Territory*> seen_territories;

    next_territories.push(current_territory);
    seen_territories.insert(current_territory);

    while(!next_territories.empty()){ // loop while there are next nodes
        Territory* territory = next_territories.top();
        next_territories.pop();
        for(Territory* neighbour: territory->neighbours){ // see each neighbour

            const bool territory_is_visited = seen_territories.find(neighbour) != seen_territories.end();
            if(!territory_is_visited){
                next_territories.push(neighbour);
                seen_territories.insert(neighbour);
            }
        }
    }

    // If the number of seen Territories from the initial territory corresponds 
    // to the number of territories in the map set, the graph is connected!
    bool map_is_connected_graph = seen_territories.size() == this->territories.size();

    if(map_is_connected_graph){
        std:: cout<< "(1) Map is a connected graph." << endl;
    }
    else{
        std:: cout<< "(1) Map is not a connected graph." << endl;
    }
    
    

    // (2) Continents are connected subgraphs

    // same idea as for (1)
    bool continents_are_connected_graphs = true;

    for(pair<int, Continent*> pair : this->continents){

        stack<Territory*> next_continent_territories;
        set<Territory*> seen_continent_territories;

        Continent* current_continent = pair.second;

        Territory* current_continent_territory = current_continent->territories.begin()->second; // take first territory in continent

        next_continent_territories.push(current_continent_territory);
        seen_continent_territories.insert(current_continent_territory);

        while(!next_continent_territories.empty()){ // loop while there are next nodes
            Territory* continent_territory = next_continent_territories.top();
            next_continent_territories.pop();
            for(Territory* neighbour: continent_territory->neighbours){ // see each neighbour

                const bool continent_territory_is_visited = seen_continent_territories.find(neighbour) != seen_continent_territories.end();
                
                const bool neighbour_belongs_to_continent = neighbour->continent_name == current_continent->name;
                
                if(!continent_territory_is_visited && neighbour_belongs_to_continent){
                    next_continent_territories.push(neighbour);
                    seen_continent_territories.insert(neighbour);
                }
            }
        }

        // If the number of seen Territories (that are in the same continent) from the initial territory in any of the continents does not corresponds 
        // to the number of territories in the that given continent set, the continents are not connected graphs
        if(!(seen_continent_territories.size() == current_continent->territories.size())){
            continents_are_connected_graphs = false;
            break;
        }
    }

    if(continents_are_connected_graphs){
        std:: cout<< "(2) Continents are connected graphs." << endl;
    }
    else{
        std:: cout<< "(2) Continents aren not connected graphs." << endl;
    }



    // (3) Each Territory belongs to one and only one continent 

    // loop through the territories in each continent and if any of them are present in other continents
    // signal false and break out of the loops

    set<Territory*> countrys_territories;
    bool territory_belong_to_one_continent = true;

    for(pair <int, Continent*> c_pair : this->continents){
        Continent* current_continent = c_pair.second;
         if(!territory_belong_to_one_continent){
                break;
            }

        for(pair <int, Territory*> t_pair: current_continent->territories){

            Territory* current_territory = t_pair.second;
            
            territory_belong_to_one_continent = countrys_territories.find(current_territory)==countrys_territories.end();

            if(!territory_belong_to_one_continent){
                break;
            }
            countrys_territories.insert(current_territory);
        }
    }

    if(territory_belong_to_one_continent){
        std:: cout<< "(3) Each territory belongs to one and only one continent." << endl;
    }
    else{
        std:: cout<< "(3) Not each of the territory belongs to one and only one continent." << endl;
    }

}

// loadMap implementation
Map* MapLoader::loadMap(string filePath) {

    // file variables
	ifstream file(filePath);
	string line;

    // parsing variables
	string territory_delimiter = ",";
    string continent_delimiter = "=";
    bool parsing_continents = false;
    bool parsing_territories = false;
    int delimiter_index = 0;

    // ids
	int continent_id = 0;
    int territory_id = 0;

    // hashmaps of continents and territories
	map<int, Continent*> continents; 
	map<int, Territory*> territories;

    // map of names to territories to link neighbours to each territory
	map<string, Territory*> territory_names_to_territories;

    // map of names to continent to add continents to map
	map<string, Continent*> continent_names_to_continents;


    // file does not exist
    if(!file){
        std::cout << filePath << " does not exist."<< endl;
    }

    // file exists
    else{
        std::cout << filePath <<  " exist."<< endl;
        
        // read each line while it exists
        //
        // This is going to be the first iteration. In this iteration, a list of territories 
        // and of continents will be generated along with a hashmap of continent names to continent 
        // pointers and a hashmap of territory names to territory pointers. The former will 
        // facilitate adding each territory to its corresponding continent graph object. The latter 
        // will serve to do the same for the map graph object and to link the neighbours on the second 
        // iteration.
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
                    std::cout << endl  << "Continent section finished ..." << endl;
                    continue;
                }
                
                else {
                    // Get continent name and calculate delimiter index
                    string continent_name = line.substr(0, line.find(continent_delimiter));
                    int index_after_last_delimiter = continent_name.length() + continent_delimiter.length();
                    
                    // get continent score
                    string score = line.substr(index_after_last_delimiter, line.find(continent_delimiter, index_after_last_delimiter));

                    // Create a continent and add it to the list of continents that will be added to the map
                    Continent* c = new Continent(continent_id, continent_name, stoi(score));
                    continents.insert(pair<int, Continent*>(continent_id, c));

                    // Add the continents name and continent pointer to the hashmap needed to locate the
                    // continent object based on the continent name once the territories are parsed
                    continent_names_to_continents.insert(pair<string, Continent*>(continent_name, c));
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
                    // get territory name and calculate delimiter index
                    int index_after_last_delimiter = 0;
                    string territory_name = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter = territory_name.length() + territory_delimiter.length();

                    // get territory x coordinate and calculate delimiter index
                    string x = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter += x.length() + territory_delimiter.length();

                    // get territory y coordinate and calculate delimiter index
                    string y = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter); 
                    index_after_last_delimiter += y.length() + territory_delimiter.length();

                    // get territory continent name and calculate delimiter index
                    string continent_name = line.substr(index_after_last_delimiter, line.find(territory_delimiter, index_after_last_delimiter) - index_after_last_delimiter);
                    index_after_last_delimiter += continent_name.length() + territory_delimiter.length();

                    // get territory neighbours as a string
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

                    // add territory name and territory pointer to hashmap
                    // this will help with the linking of neighbours
                    territory_names_to_territories.insert(pair<string, Territory*>(territory_name, territory));

                    // Add territories to the hashmap that will be added to the map object
                    territories.insert(pair<int, Territory*>(territory_id, territory));

                    // Add territory to hashmap of territories in the continent that matches the name of the territory continent
                    continent_names_to_continents[continent_name]->territories.insert(pair<int, Territory*>(territory_id, territory));

                    territory_id++;
                }
            }
        }

        // On this second iteration, each territory is linked as to  hold
        // a list of pointers to its neighbour objects.
        Territory *neighbouring_territory;
        vector<Territory*> neighbours;

        // Iterrate throught the list of territories to add neighbours
        for(pair <int, Territory*> id_and_territory : territories){

            // clear list of neighbours
            neighbours.clear();

            // for each of the territories, iterate through its list of territory names 
            // added in the first teration to find the territory object
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

        // Iterrate throught the list of territories to add neighbours
        for(pair <int, Continent*> id_and_continent : continents){

            // Continent:
            std::cout<< id_and_continent.second->name<<endl;


            for(pair <int, Territory*> t : id_and_continent.second->territories){
                // Territories in that continent:
                std::cout << t.second->name << ",";
            }
            std::cout<< endl;
        }    
    }

    // close file
    file.close();

    // If file does not exists, return an empty map, otherwise return map with parsed information
    Map* map_result = new Map(continents, territories);
    return map_result;
}