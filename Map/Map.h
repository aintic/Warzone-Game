/**
 * @file Map.h
 * @author Michael Djabauri
 * @date 2022-10-06
 */

#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Player;

//*****************************************************************
// Territory: Represents the territory of a map (node of the graph)
//Territory class
class Territory
{
public:
    //Constructor: Construct a new Territory object
    Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings);

    //Copy constructor: Construct a new Territory object
    Territory(const Territory &t);

    //Destructor: Destroy the Territory object
    ~Territory();

    //stream insertion operator
    friend ostream& operator <<(ostream& stream, const Territory& t);

    //assignment operator
    Territory& operator=(const Territory& t);

    // Getters and setters
    int get_id() const;
    void set_id(int id);

    int get_army_units() const;
    void set_army_units(int army_units);

    int get_issued_army_units() const;
    void set_issued_army_units(int army_units);

    string get_name();
    void set_name(string name);

    int get_x();
    void set_x(int x);

    int get_y();
    void set_y(int y);

    int get_continent_id();
    void set_continent_id(int continent_id);

    string get_continent_name();
    void set_continent_name(string continent_name);

    vector<string> get_neighbours_strings();
    void set_neighbours_strings(vector<string> neighbours_strings);

    vector<Territory*> get_neighbours();
    void set_neighbours(vector<Territory*> neighbours);

    Player* get_owner();
    void set_owner(Player* player);

private:
    Player* owner;
    int id;
    int army_units{};
    int issuedArmyUnits; // number of army units that are waiting to be executed
    string name;
    int x;
    int y;
    int continent_id{};
    string continent_name;
    vector <string> neighbours_strings; // placeholder before adding the pointers to the neighbours
    vector <Territory*> neighbours;
};


//*****************************************************************
// Continent: represents the continent of a map. Is a connected subgraph of a map.

//Continent Class
class Continent
{
public:

    //brief Constructor: Construct a new Continent object
    Continent(int id, string name, int score);

    // Copy constructor: Construct a new Continent object
    Continent(const Continent &c);

    //Destructor: Destroy the Continent object
    ~Continent();

    //Assignment Operator
    Continent& operator=(const Continent& c);

    //Stream Insertion operator
    friend ostream& operator <<(ostream& stream, const Continent& c);

    // getters and setters

    int get_id();
    void set_id(int id);

    string get_name();
    void set_name(string name);

    int get_score();
    void set_score(int score);

    map <int, Territory*> get_territories();
    void set_territories(map <int, Territory*> territories);

    //Get the continent size object
    int get_continent_size();

    //Add a territory
    void add_territory(pair<int, Territory*> pair);

private:
    int id;
    string name;
    int score;
    // hashmap of territory ids to territories where each territory points to its neighbours
    map<int, Territory*> territories;
};



//*****************************************************************
// Map: is a connected graph representing a collection of territory

//Map Class
class Map
{
public:
    //Constructor: Construct a new Map object
    Map(string name, map<int, Continent*> continents, map<int, Territory*> territories);

    //Copy constructor: Construct a new Map object
    Map(const Map& m);

    //Destructor: Destroy the Map object
    ~Map();

    //Assignment operator
    Map& operator=(const Map& m);

    //Validate that the map is a connected graph,
    //the continents are connected subgraphs, and each territory
    //belongs to one and only one continent
    void validate();

    //Assignment insertion operator
    friend ostream& operator <<(ostream& stream, const Map& m);

    // Getters and setters

    string get_name();
    void set_name(string name);

    map<int, Territory*> get_territories();
    void set_territories(map<int, Territory*> territories);

    map<int, Continent*> get_continents();
    void set_continents(map<int, Continent*> continents);

    bool get_valid();

    int allContinentsBonus(Player* player);

private:
    string name;
    // hashmap of continent ids to continent where each territory holds a map of its territories
    map<int, Continent*> continents;

    // hashmap of territory ids to territories where each territory points to its neighbours
    map<int, Territory*> territories;

    bool valid;
};



//
//MAP LOADER CLASS
//

//Map loader Class
class MapLoader
{
public:
   //Constructor: Construct a new Map Loader object
    MapLoader();

    //Copy constructor: Construct a new MapLoader object
    MapLoader(const MapLoader &m);

    //Destructor: Destroy the Map Loader object
    ~MapLoader();

    //Stream insertion operator
    friend ostream& operator <<(ostream& stream, const MapLoader& m);

    //Assignment operator
    MapLoader& operator=(const MapLoader& m);

    //Load map
    static Map* loadMap(string filePath);
};