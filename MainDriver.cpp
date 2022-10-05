// include your headers
#include "iostream"
#include "Map.h"

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