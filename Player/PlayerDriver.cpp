#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include <map>
#include <vector>

using namespace std;

void testPlayers() {

    GameEngine* game = new GameEngine;
    Player *p1 = new Player("player1", game);
    Player *p2 = new Player("player2", game);

    vector<string> neighbor1 = {"t2", "t5"};
    vector<string> neighbor2 = {"t1", "t5"};
    vector<string> neighbor3 = {"t1", "t4"};
    vector<string> neighbor4 = {"t3", "t5"};
    vector<string> neighbor5 = {"t4"};

    //Creating a map for testing purposes
    Continent* c1 = new Continent(1, "c1", 5);
    Continent* c2 = new Continent(2, "c2", 2);
    Continent* c3 = new Continent(3, "c3", 10);
    Territory* t1 = new Territory(1,"t1","c1",0,0, neighbor1);
    Territory* t2 = new Territory(2,"t2","c1",1,1, neighbor2);
    Territory* t3 = new Territory(3,"t3","c2",2,2, neighbor3);
    Territory* t4 = new Territory(4,"t4","c3",3,3, neighbor4);
    Territory* t5 = new Territory(5,"t5","c1",4,4, neighbor5);

    vector<Territory*> neighbors1 = {t2, t5};
    vector<Territory*> neighbors2 = {t1, t5};
    vector<Territory*> neighbors3 = {t1, t4};
    vector<Territory*> neighbors4 = {t3, t5};
    vector<Territory*> neighbors5 = {t4};

    t1->set_neighbours(neighbors1);
    t2->set_neighbours(neighbors2);
    t3->set_neighbours(neighbors3);
    t4->set_neighbours(neighbors4);
    t5->set_neighbours(neighbors5);

    //Adding territories in continents
    c1->add_territory(pair<int, Territory*>(t1->get_id(),t1));
    c1->add_territory(pair<int, Territory*>(t2->get_id(),t2));
    c2->add_territory(pair<int, Territory*>(t3->get_id(),t3));
    c3->add_territory(pair<int, Territory*>(t4->get_id(),t4));
    c1->add_territory(pair<int, Territory*>(t5->get_id(),t5));

    map<int, Continent*> continents;//Continents hashmap
    map<int, Territory*> territories;//Territories hashmap
    continents.insert(pair<int, Continent*>(c1->get_id(),c1));
    continents.insert(pair<int, Continent*>(c2->get_id(),c2));
    continents.insert(pair<int, Continent*>(c3->get_id(),c3));

    //Creating map object
    Map* map = new Map("map 1", continents, territories);
    //Displaying map
    cout << *map << endl;

    //Linking map and players to gameEngine
    game->map = map;
    map->set_name("madeUpMap");
    game->players.push_back(p1);
    game->players.push_back(p2);


    // load the testing map
    string mapName = "testingMap";
    string map_path = "Maps/" + mapName + ".map";
    game->map = MapLoader::loadMap(map_path);

    if(game->map == nullptr){
        cout << "Could not load the map <" + mapName + ">";
    }
    else{
        cout << "Loaded map <" + mapName + ">";
    }

    //validate the map
    game->map->validate();

    //Testing reinforcement phase
    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t5);

    p2->addTerritory(t3);
    p2->addTerritory(t4);

    cout << *game->getDeck() << endl;

    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);

    cout << *game->getDeck() << endl;

    cout << "\n\nContinent bonus for p1: ";
    cout << game->map->allContinentsBonus(p1) << endl;
    cout << "Continent bonus for p2: ";
    cout << game->map->allContinentsBonus(p2) << endl;

    cout << "Player 1 currently owns : " << p1->getNumTerritories() << " territories" << endl;
    cout << "Player 2 currently owns : " << p2->getNumTerritories() << " territories" << endl;

    t1->set_army_units(10);
    t2->set_army_units(2);
    t3->set_army_units(9);
    t4->set_army_units(7);
    t5->set_army_units(4);

    cout << "Strongest owned neighbor" << endl;
    cout << *p2->strongestOwnedNeighbor(t1);
    cout << *p2->strongestOwnedNeighbor(t2);
    cout << *p1->strongestOwnedNeighbor(t3);
    cout << *p1->strongestOwnedNeighbor(t4);
    cout << *p2->strongestOwnedNeighbor(t5);

    game->mainGameLoop();
}