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
//*****************************************************************
// Territory

/**
 * @brief Territory class
 * 
 */
class Territory 
{
    public:
    /**
     * @brief Constructor: Construct a new Territory object
     * 
     * @param id 
     * @param name 
     * @param continent_name 
     * @param x 
     * @param y 
     * @param neighbours_strings 
     */
	Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings);

	/**
	 * @brief Copy constructor: Construct a new Territory object
	 * 
	 * @param t 
	 */
	Territory(const Territory &t);

    /**
     * @brief Destructor: Destroy the Territory object
     * 
     */
	~Territory();

	/**
	 * @brief Stream insertion operator
	 * 
	 * @param stream 
	 * @param t 
	 * @return ostream& 
	 */
	friend ostream& operator <<(ostream& stream, const Territory& t);

	/**
	 * @brief Assignment operator
	 * 
	 * @param p 
	 * @return Territory& 
	 */
    Territory& operator=(const Territory& t); 

	// Getters and setters
	int get_id();
	void set_id(int id);

	int get_army_units();
	void set_army_units(int army_units);
	
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

	private:
	int id;
	int army_units;
	string name;
	int x;
	int y;
    int continent_id;
	string continent_name;
	vector <string> neighbours_strings; // placeholder before adding the pointers to the neighbours
    vector <Territory*> neighbours;
};




//*****************************************************************
// Continent

/**
 * @brief Contonent Class
 * 
 */
class Continent
{
    public:

	/**
	 * @brief Constructor: Construct a new Continent object
	 * 
	 * @param id 
	 * @param name 
	 * @param score 
	 */
	Continent(int id, string name, int score);

	/**
	 * @brief Copy constructor: Construct a new Continent object
	 * 
	 * @param c 
	 */
	Continent(const Continent &c);

	/**
	 * @brief Destructor: Destroy the Continent object
	 * 
	 */
	~Continent();

	/**
	 * @brief Assignment Operator 
	 * 
	 * @param c 
	 * @return Continent& 
	 */
    Continent& operator=(const Continent& c); 

	/**
	 * @brief Stream Insertion operator
	 * 
	 * @param stream 
	 * @param t 
	 * @return ostream& 
	 */
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

	/**
	 * @brief Get the continent size object
	 * 
	 * @return int 
	 */
	int get_continent_size();

	/**
	 * @brief Add a territory
	 * 
	 */
	void add_territory(pair<int, Territory*> pair);

	private:
	int id;
	string name;
    int score;
	// hashmap of territory ids to territories where each territory points to its neighbours
	map<int, Territory*> territories; 
};



//*****************************************************************
// Map

/**
 * @brief Map Class
 * 
 */
class Map
{
	// data members
    public:

	// hashmap of continent ids to continent where each territory holds a map of its territories
	map<int, Continent*> continents; 

	// hashmap of territory ids to territories where each territory points to its neighbours
	map<int, Territory*> territories; 
	bool valid;
	
	// member functions
	
	// validate method
	void validate();

    // constructors
	Map();
	Map(const Map& m);
	Map(map<int, Continent*> continents, map<int, Territory*> territories);

	// destructor
	~Map();


};




//*****************************************************************
// Map Loader

/**
 * @brief Map loader Class
 * 
 */
class MapLoader
{
	// data members
	
	// member functions
    public:
	static Map* loadMap(string filePath);
};


