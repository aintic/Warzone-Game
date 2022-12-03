/**
 * @file Map.cpp
 * @author Michael Djabauri
 * @date 2022-10-07
 */

#include "Map.h"
#include "../Player/Player.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <set>
using namespace std;

//*****************************************************************
// Territory: Represents the territory of a map (node of the graph)


/**
 * @brief Constructor: Construct a new Territory:: Territory object
 * 
 * @param id 
 * @param name 
 * @param continent_name 
 * @param x 
 * @param y 
 * @param neighbours_strings 
 */
Territory::Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings) {
	Player *owner;
    this->id = id;
	this->name = name;
	this->x = x;
	this->y = y;
    this->continent_name = continent_name;
    this->neighbours_strings = neighbours_strings;
    this->issuedArmyUnits = 0; // number of army units that are waiting to be executed
}

/**
 * @brief Copy constructor: Construct a new Territory:: Territory object
 * 
 * @param t 
 */
Territory::Territory(const Territory &t){
    owner = t.owner;
    id = t.id;
	army_units = t.army_units;
    issuedArmyUnits = t.issuedArmyUnits;
	name = t.name;
	x = t.x;
	y = t.y;
    continent_id = t.continent_id;
	continent_name = t.continent_id;
	neighbours_strings = t.neighbours_strings;
}

/**
 * @brief Stream insertion operator
 * 
 * @param stream 
 * @param t 
 * @return ostream& 
 */
ostream& operator <<(ostream& stream, const Territory& t){
    string neighbours = "";
    for(string neighbour: t.neighbours_strings){
        neighbours.append(neighbour + " ");
    }
    stream << "Territory: "<< t.name << ", ID:"<< t.id <<", Continent: " 
    << t.continent_name << ", \n\t\t\tNeighbours: " << neighbours<< endl;
    return stream;
}

/**
 * @brief Assignment operator
 * 
 * @param t 
 * @return Territory& 
 */
Territory& Territory::operator=(const Territory& t){
    if(&t != this) {
        owner = t.owner;
        id = t.id;
        army_units = t.army_units;
        issuedArmyUnits = t.issuedArmyUnits;
        name = t.name;
        x = t.x;
        y = t.y;
        continent_id = t.continent_id;
        continent_name = t.continent_name;
        neighbours_strings = t.neighbours_strings;
        neighbours = t.neighbours;
    }
    return *this;
}

/**
 * @brief Destructor: Destroy the Territory:: Territory object
 * 
 */
Territory::~Territory() {
	name.clear();
	continent_name.clear();
	neighbours_strings.clear();
    neighbours.clear();
}

// Getters and Setters

int Territory::get_id() const
{
    return this->id;
}
void Territory::set_id(int id)
{
    this->id = id;
}

int Territory::get_army_units() const
{
    return this->army_units;
}
void Territory::set_army_units(int army_units)
{
    this->army_units = army_units;
}

int Territory::get_issued_army_units() const
{
    return this->issuedArmyUnits;
}
void Territory::set_issued_army_units(int army_units)
{
    this->issuedArmyUnits = army_units;
}

string Territory::get_name()
{
    return this->name;
}
void Territory::set_name(string name)
{
    this->name = name;
}

int Territory::get_x()
{
    return this->x;
}
void Territory::set_x(int x)
{
    this->x = x;
}

int Territory::get_y()
{
    return this->y;
}
void Territory::set_y(int y)
{
    this->y = y;
}

int Territory::get_continent_id()
{
    return this->continent_id;
}
void Territory::set_continent_id(int continent_id)
{
    this->continent_id = continent_id;
}

string Territory::get_continent_name()
{
    return this->continent_name;
}
void Territory::set_continent_name(string continent_name)
{
    this->continent_name = continent_name;
}

vector<string> Territory::get_neighbours_strings()
{
    return this->neighbours_strings;
}
void Territory::set_neighbours_strings(vector<string> neighbours_strings)
{
    this->neighbours_strings = neighbours_strings;
}

vector<Territory*> Territory::get_neighbours(){
    return this->neighbours;
}
void Territory::set_neighbours(vector<Territory*> neighbours){
    this->neighbours = neighbours;
}

void Territory::set_owner(Player* player){
    this->owner = player;
}

Player* Territory::get_owner() {
    return this->owner;
}

//*****************************************************************
// Continent: represents the continent of a map. Is a connected subgraph of a map.

/**
 * @brief Constructor: Construct a new Continent:: Continent object
 * 
 * @param id 
 * @param name 
 * @param score 
 */
Continent::Continent(int id, string name, int score) {
	this->id = id;
	this->name = name;
    this->score = score;
}

/**
 * @brief Copy constructor: Construct a new Continent:: Continent object
 * 
 * @param c 
 */
Continent::Continent(const Continent &c){
    id = c.id;
	name = c.name;
	score = c.score;
}

/**
 * @brief Destructor: Destroy the Continent:: Continent object
 * 
 */
Continent::~Continent() {
	name.clear();
    // intentionally do not delete the territory pointers
    territories.clear();
}

/**
 * @brief Assignment operator
 * 
 * @param c 
 * @return Continent& 
 */
Continent& Continent::operator=(const Continent& c){
    id = c.id;
	name = c.name;
	score = c.score;
	territories = c.territories;

    return *this;
}

/**
 * @brief Stream insertion operator
 * 
 * @param stream 
 * @param c 
 * @return ostream& 
 */
ostream& operator <<(ostream& stream, const Continent& c){

    stream << "Continent: "<< c.name << ", ID:"<< c.id <<", Score: " 
    << c.score << ", Territories:" << endl;

    for(pair<int, Territory*> pair: c.territories){
        stream << "\t\t" << *pair.second;
    }

    return stream;
}


// Getters and setters
int Continent::get_id()
{
    return this->id;
}
void Continent::set_id(int id)
{
    this->id = id;
}

string Continent::get_name()
{
    return this->name;
}
void Continent::set_name(string name)
{
    this->name = name;
}

int Continent::get_score()
{
    return this->score;
}
void Continent::set_score(int score)
{
    this->score = score;
}

map <int, Territory*> Continent::get_territories()
{
    return this->territories;
}
void Continent::set_territories(map <int, Territory*> territories)
{
    this->territories = territories;
}

/**
 * @brief Get the continent size object
 * 
 * @return int 
 */
int Continent::get_continent_size()
{
    return this->territories.size();
}

void Continent::add_territory(pair< int, Territory*> pair)
{
    this->territories.insert(pair);
}


//*****************************************************************
// Map: is a connected graph representing a collection of territor

/**
 * @brief Constructor: Construct a new Map:: Map object
 * 
 * @param continents 
 * @param territories 
 */
Map::Map(string name, map<int, Continent*> continents, map<int, Territory*> territories) {
    this->name = name;
	this->continents = continents;
	this->territories = territories;
}

/**
 * @brief Copy constructor: Construct a new Map:: Map object
 * 
 * @param m 
 */
Map::Map(const Map &m){
    name = m.name;
    continents = m.continents;
    territories = m.territories;
}

/**
 * @brief Destructor: Destroy the Continent:: Continent object
 * 
 */
Map::~Map() {
	name.clear();
    
    for(pair<int, Continent*> pair : continents){
        Continent * continent = pair.second;
        delete continent; // free memory
        continent = nullptr;
    }
    continents.clear();

    for(pair<int, Territory*> pair : territories){
        Territory * territory = pair.second;
        delete territory; // free memory
        territory = nullptr;
    }
    territories.clear();
}

/**
 * @brief Assignment operator
 * 
 * @param m 
 * @return Map& 
 */
Map& Map::operator=(const Map& m){
	name = m.name;
    continents = m.continents;
	territories = m.territories;

    return *this;
}

/**
 * @brief Assignments insertion operator
 * 
 * @param stream 
 * @param m 
 * @return ostream& 
 */
ostream& operator <<(ostream& stream, const Map& m){

    stream << "Map path: "<< m.name << endl << "Continents:" << endl;

    for(pair<int, Continent*> pair: m.continents){
        stream << "\t" << *pair.second;
    }

    return stream;
}

// Getters and setters:

string Map::get_name()
{
    return this->name;
}
void Map::set_name(string name)
{
    this->name = name;
}

map<int, Territory*> Map::get_territories()
{
    return this->territories;
}
void Map::set_territories(map<int, Territory*> territories)
{
    this->territories = territories;
}

map<int, Continent*> Map::get_continents()
{
    return this->continents;
}
void Map::set_continents(map<int, Continent*> continents)
{
    this->continents = continents;
}

bool Map::get_valid()
{
    return this->valid;
}

/**
 * @brief Validate that the map is a connected graph, 
 * the continents are connected subgrahs, and each territitory 
 * belongs to one and only one continent 
 * 
 */
void Map::validate(){

    std::cout<< "Starting validate() for "<< this->get_name()<< endl <<endl;
    // (1) Map is connected subgraph
    
    // To confirm that the map is a connected graph we start with the first territory in 
    // the map and visit each of its territories in a DFS-like manner. we keep a count of
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
        for(Territory* neighbour: territory->get_neighbours()){ // see each neighbour

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
        std:: cout<< "(1) Map is a connected graph :)" << endl;
    }
    else{
        std:: cout<< "(1) Map is not a connected graph :(" << endl;
    }
    

    // (2) Continents are connected subgraphs

    // same idea as for (1)
    bool continents_are_connected_graphs = false;

    for(pair<int, Continent*> pair : this->continents){

        stack<Territory*> next_continent_territories;
        set<Territory*> seen_continent_territories;

        Continent* current_continent = pair.second;

        Territory* current_continent_territory = current_continent->get_territories().begin()->second; // take first territory in continent

        next_continent_territories.push(current_continent_territory);
        seen_continent_territories.insert(current_continent_territory);

        while(!next_continent_territories.empty()){ // loop while there are next nodes
            Territory* continent_territory = next_continent_territories.top();
            next_continent_territories.pop();
            for(Territory* neighbour: continent_territory->get_neighbours()){ // see each neighbour

                const bool continent_territory_is_visited = seen_continent_territories.find(neighbour) != seen_continent_territories.end();
                
                const bool neighbour_belongs_to_continent = neighbour->get_continent_name() == current_continent->get_name();
                
                if(!continent_territory_is_visited && neighbour_belongs_to_continent){
                    next_continent_territories.push(neighbour);
                    seen_continent_territories.insert(neighbour);
                }
            }
        }

        // If the number of seen Territories (that are in the same continent) from the initial territory in any of the continents does not corresponds 
        // to the number of territories in the that given continent set, the continents are not connected graphs

        continents_are_connected_graphs = seen_continent_territories.size() == current_continent->get_continent_size();

        if(!continents_are_connected_graphs){
            break;
        }
    }

    if(continents_are_connected_graphs){
        std:: cout<< "(2) Continents are connected subgraphs :)" << endl;
    }
    else{
        std:: cout<< "(2) Continents aren not connected subgraphs :(" << endl;
    }



    // (3) Each Territory belongs to one and only one continent 

    // loop through the territories in each continent and if any of them are present in other continents
    // signal false and break out of the loops

    set<Territory*> countrys_territories;
    bool territory_belong_to_one_continent = false;

    for(pair <int, Continent*> c_pair : this->continents){
        Continent* current_continent = c_pair.second;

        for(pair <int, Territory*> t_pair: current_continent->get_territories()){

            Territory* current_territory = t_pair.second;
            
            territory_belong_to_one_continent = countrys_territories.find(current_territory)==countrys_territories.end();

            if(!territory_belong_to_one_continent){
                break;
            }
            countrys_territories.insert(current_territory);
        }
    }

    if(territory_belong_to_one_continent){
        std:: cout<< "(3) Each territory belongs to one and only one continent :)" << endl;
    }
    else{
        std:: cout<< "(3) Not each of the territory belongs to one and only one continent :(" << endl;
    }

    bool valid = territory_belong_to_one_continent && map_is_connected_graph && continents_are_connected_graphs;

    if (valid){
        std::cout << endl << this->get_name() << " is VALID :)"<< endl <<endl;
        this->valid = true;
    }
    else{
        std::cout << endl << this->get_name() << " is INVALID :("<< endl <<endl;
        this->valid = false;
    }
}

//returns sum of bonuses to player if they own all territories
//in one continent
int Map::allContinentsBonus(Player* player) {
    int bonus = 0;
    for(auto & x : continents){
        int count = 0;
        int continentSize = x.second->get_continent_size();
        for(auto const& y : player->getTerritories()){
            if(y->get_continent_name() == x.second->get_name()){
                count++;
            }
        }
        if(continentSize == count){
            bonus += x.second->get_score();
        }
    }
    return bonus;
}

//
//MAP LOADER CLASS
//


/**
 * @brief Constructor: Construct a new Map Loader object
 *
 */
MapLoader::MapLoader(){
}

/**
 * @brief Copy constructor: Construct a new MapLoader object
 * @param m
 */
MapLoader::MapLoader(const MapLoader &m){
}

/**
 * @brief Destructor: Destroy the Map Loader object
 *
 */
MapLoader::~MapLoader(){
}

/**
 * @brief Stream insertion operator
 *
 * @param stream
 * @param m
 * @return ostream&
 */
ostream& operator <<(ostream& stream, const MapLoader& c){
    stream << " MapLoader" << endl;
    return stream;
}

/**
 * @brief Assignment operator
 *
 * @param t
 * @return MapLoader&
 */
MapLoader& MapLoader::operator=(const MapLoader& t){
    return *this;
}

/**
 * @brief Load Map implementation that reads a txt file
 * 
 * @param filePath 
 * @return Map* 
 */
Map* MapLoader::loadMap(string filePath) {

    std::cout << endl <<"Starting loadMap() for "<< filePath << endl;
    // file variables
	ifstream file(filePath);
	string line;

    // parsing variables
	string territory_delimiter = ",";
    string continent_delimiter = "=";
    bool parsing_continents = false;
    bool parsing_territories = false;

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
        std::cout << endl << filePath << " REJECTED (file does not exist)"<< endl;
        return nullptr;
    }

    // file exists
    else{        
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
            }

            // flag parsing territories
            if(line.find("[Territories]") != std::string::npos) {
                parsing_continents = false;
                parsing_territories = true;
            }

            // Parse continents
            if (parsing_continents && line.find("[Continents]") == std::string::npos) {

                if (line.find(continent_delimiter) == std::string::npos) { // skip line if does not have the continent delimiter
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
                    continent_id++;
                }
            }

            // Parse territories
            else if (parsing_territories && line.find("[Territories]") == std::string::npos) {
                
                if (line.find(territory_delimiter) == std::string::npos) { // skip line if does not have the territory delimiter
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
                  
                    string neighbour;
                    // while there is a delimiter in the string of neighbours add the territory
                    while((line_neighbours.find(territory_delimiter) != std::string::npos)){
                        int delimiter_index = line_neighbours.find(territory_delimiter);
                        neighbour = line_neighbours.substr(0, delimiter_index);
                        line_neighbours = line_neighbours.substr(delimiter_index + territory_delimiter.length());
                        neighbours_strings.push_back(neighbour);
                    }

                    // remove last empty character if it is the carriage return, represented by 13 in ascii
                    if ((int)line_neighbours[line_neighbours.length() - 1] == 13){
                        line_neighbours = line_neighbours.substr(0, line_neighbours.length()-1);
                    }
                    
                    // Add last neighbour
                    neighbours_strings.push_back(line_neighbours);

                    // construct territory and add it to list
                    Territory* territory = new Territory(territory_id, territory_name, continent_name, stoi(x), stoi(y), neighbours_strings);
                    // add territory name and territory pointer to hashmap
                    // this will help with the linking of neighbours
                    territory_names_to_territories.insert(pair<string, Territory*>(territory_name, territory));

                    // Add territories to the hashmap that will be added to the map object
                    territories.insert(pair<int, Territory*>(territory_id, territory));

                    if(continent_names_to_continents.empty()){
                        std::cout << endl << filePath << " REJECTED (file does not have continents)"<< endl << endl;
                        return nullptr;
                    }

                    // Add territory to hashmap of territories in the continent that matches the name of the territory continent
                    continent_names_to_continents[continent_name]->add_territory(pair<int, Territory*>(territory_id, territory));
                    territory_id++;
                }
            }
        }

        // On this second iteration, each territory is linked as to  hold
        // a list of pointers to its neighbour objects.
        Territory *neighbouring_territory;
        vector<Territory*> neighbours;

        // Iterate through the list of territories to add neighbours
        for(pair <int, Territory*> id_and_territory : territories){

            // clear list of neighbours
            neighbours.clear();

            // for each of the territories, iterate through its list of territory names 
            // added in the first iteration to find the territory object
            for(string neighbour_name_string : id_and_territory.second->get_neighbours_strings()){

                // get neighbour territory and add it to list     
                neighbouring_territory =  territory_names_to_territories[neighbour_name_string];
                neighbours.push_back(neighbouring_territory);
            }
            
            // add list of its neighbours to each territory object
            id_and_territory.second->set_neighbours(neighbours);
        }
    }

    // close file
    file.close();

    // If file does not exist, return an empty map, otherwise return map with parsed information
    Map* map_result = new Map(filePath, continents, territories);
    std::cout << endl << "Successfully created a map object for "<< filePath << endl;
    return map_result;
}