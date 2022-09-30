#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Territory 
class Territory 
{
	// data members:
    public:
    int id;
	string name;
	int x;
	int y;
    int continent_id;
	string continent_name;
	vector <string> neighbours_strings;
    vector <Territory*> neighbours;

	// member functions
	// constructor
	Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings);

    // destructor
	~Territory();

	void add_neighbours(vector <Territory*> neighbours);
};


// Continent
class Continent
{
	// data members
    public:
    // variables
    int id;
	string name;
    int score;

	// member functions
	// constructor
	Continent(int id, string name, int score);

	// destructor
	~Continent();
};

// Map
class Map
{
	// data members
    public:
	vector<Continent*> continents; // list of continents

	map<int, Territory*> territories; // list of territories
	bool valid;
	
	// member functions
    // constructors
	Map();
	Map(const Map& m);
	Map(vector<Continent*> continents, map<int, Territory*> territories);

	// destructor
	~Map();


};

// Map Loader
class MapLoader
{
	// data members
	
	// member functions
    public:
	static Map* loadMap(string filePath);
};

