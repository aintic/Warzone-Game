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
	int army_units;

	string name;
	int x;
	int y;
    int continent_id;
	string continent_name;
	vector <string> neighbours_strings; // placeholder before adding the pointers to the neighbours
    vector <Territory*> neighbours;

	// member functions
	// constructor
	Territory(int id, string name, string continent_name, int x, int y, vector <string>  neighbours_strings);

    // destructor
	~Territory();

	friend ostream& operator <<(ostream& stream, const Territory& t);

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

	// hashmap of territory ids to territories where each territory points to its neighbours
	map<int, Territory*> territories; 

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

// Map Loader
class MapLoader
{
	// data members
	
	// member functions
    public:
	static Map* loadMap(string filePath);
};

// free function to test and load maps
vector <Map*> testLoadMaps(vector <string> map_files);

