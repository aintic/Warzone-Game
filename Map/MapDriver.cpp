#include <iostream>
#include "Map.h"

using namespace std;
int main()
{
	string filePath = "Annys Piratenwelt.map";

	Map* map = MapLoader::loadMap(filePath);
}
