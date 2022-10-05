#include <iostream>
#include "Map.h"

using namespace std;
int main()
{
	// map files
	vector<string> filePaths {"Annys Piratenwelt.map"};

	// map objects
	vector <Map*> maps = testLoadMaps(filePaths);

	for(Map *map : maps){
		map->validate();
	}
}

// Test and Load Maps free function
vector <Map*> testLoadMaps(vector <string> map_files){
	vector <Map*> maps;

	// read diff map_files and creates a map object
	for(string map_file: map_files){
		maps.push_back(MapLoader::loadMap(map_file));
	}

	// TODO: reject invalid map files

	return maps;
}
