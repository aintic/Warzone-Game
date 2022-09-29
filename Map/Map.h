#include <iostream>
#include <vector>

using namespace std;

// Territory 
class Territory 
{
    public:
    int id;
	string name;
	int x;
	int y;
    int continent_id;
    vector <Territory*> neighbours;

	// constructor
	Territory(int id, string name, int x, int y, int continent_id);

    // destructor
	~Territory();
};


// Continent
class Continent
{
    public:
    // variables
    int id;
	string name;
    int score;

	// constructor
	Continent(int id, string name, int score);

	// destructor
	~Continent();
};

// Map
class Map
{
    public:
	vector<Continent*> continents; // list of continents
	vector<Territory*> territories; // list of countries
	bool valid;
    // constructors
	Map();
	Map(const Map& m);
	Map(vector<Continent*> continents, vector<Territory*> territories);

	// destructor
	~Map();


};

// Map Loader
class MapLoader
{
    public:
	static Map* loadMap(string filePath);
};

