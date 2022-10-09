#include <iostream>
#include "MapDriver.h"
#include "Map.h"

// Test and Load Maps free function
void testLoadMaps(){

	const bool show_maps = false;

	// MAP FILES:
	
	// Valid Maps:
	string valid_map = "Map/Maps/Annys Piratenwelt.map";

	// Invalid Maps:
	string file_does_not_exist = "Map/Maps/FileDoesNotExist.map";
	string continent_does_not_exist = "Map/Maps/NoContinent.map";


	vector<string> filePaths {
		valid_map, 
		file_does_not_exist,
		continent_does_not_exist
	};

	vector<Map*> maps;


	// LOAD MAPS:
	// (1) Read map_files 
	// (2) Creates a map object if valid
	// (3) Reject if invalid 
	for(string map_file: filePaths){
		maps.push_back(MapLoader::loadMap(map_file));
	}

	if(show_maps){
			
		for(Map* map: maps){
			if(map){
				std::cout<< *map << endl;
			}
		}
	}


	for(Map* map: maps){
		if(map){
			map->validate();
		}
	}

	//TODO: reject invalid map files

	// free up memory by deleting the map
	for(Map* map: maps){
		delete map;
		map = NULL;
	}

}
