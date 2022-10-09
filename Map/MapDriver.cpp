#include <iostream>
#include "MapDriver.h"
#include "Map.h"

// Test and Load Maps free function
void testLoadMaps(){

	// map files
	vector<string> filePaths {"Map/Maps/Annys Piratenwelt.map"};
	vector<Map*> maps;


	// read diff map_files and creates a map object
	for(string map_file: filePaths){
		maps.push_back(MapLoader::loadMap(map_file));
	}

	for(Map* map: maps){
		std::cout<< *map << endl;
	}

	for(Map* map: maps){
		map->validate();
	}

	//TODO: reject invalid map files

	// free up memory by deleting the map
	for(Map* map: maps){
		delete map;
		map = NULL;
	}

}
