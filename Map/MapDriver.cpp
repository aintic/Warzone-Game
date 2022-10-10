#include <iostream>
#include "MapDriver.h"
#include "Map.h"

// Test and Load Maps free function
void testLoadMaps(){

	const bool show_maps = false;

	// MAP FILES:
	
	// Valid Maps:
	string valid_map1 = "Map/Maps/AnnysPiratenwelt.map";
	string valid_map2 = "Map/Maps/Aden.map";
	string valid_map3 = "Map/Maps/DigDug.map";

	// Rejected Map Files:
	string file_does_not_exist = "Map/Maps/FileDoesNotExist.map";
	string continent_does_not_exist = "Map/Maps/NoContinent.map";

	// invalid Maps
	string continents_not_connected_graph = "Map/Maps/MongolEmpire1294.map";
	string map_not_connected_graph = "Map/Maps/Map_not_connected_graph.map";

	vector<string> filePaths {
		valid_map1, 
		valid_map2, 
		valid_map3, 
		file_does_not_exist,
		continent_does_not_exist,
		continents_not_connected_graph,
		map_not_connected_graph
	};

	vector<Map*> maps;


	// LOAD MAPS:
	// (1) Read map_files 
	// (2) Creates a map object if valid
	// (3) Reject if invalid 
	std::cout << "*********************************** LOADING MAPS ***********************************" << endl;
	for(string map_file: filePaths){
		maps.push_back(MapLoader::loadMap(map_file));
	}

	// DISPLAY MAPS:
	if(show_maps){
			
		for(Map* map: maps){
			if(map){
				std::cout<< *map << endl;
			}
		}
	}

	// VALIDATE MAPS
	std::cout << "********************************** VALIDATING MAPS *********************************" << endl;
	for(Map* map: maps){
		if(map){
			map->validate();
		}
	}

	// free up memory by deleting the map
	for(Map* map: maps){
		delete map;
		map = NULL;
	}

}
