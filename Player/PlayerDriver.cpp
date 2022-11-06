#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include <map>
#include <vector>

using namespace std;

void testPlayers() {

    Player *p1 = new Player;
    cout << p1->getPlayerID() << endl;
    Player *p2 = new Player;
    cout << p2->getPlayerID() << endl;

    GameEngine* game = new GameEngine;

    vector<string> neighbor = {"t1", "t2", "t3", "t4", "t5"};

    //Creating a map for testing purposes
    Continent* c1 = new Continent(1, "c1", 5);
    Continent* c2 = new Continent(2, "c2", 2);
    Continent* c3 = new Continent(3, "c3", 10);
    Territory* t1 = new Territory(1,"t1","c1",0,0, neighbor);
    Territory* t2 = new Territory(2,"t2","c1",1,1, neighbor);
    Territory* t3 = new Territory(3,"t3","c2",2,2, neighbor);
    Territory* t4 = new Territory(4,"t4","c3",3,3, neighbor);
    Territory* t5 = new Territory(5,"t5","c1",4,4, neighbor);

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
    //cout << *map << endl;

    //Linking map and players to gameEngine
    game->map = map;
    game->players.push_back(p1);
    game->players.push_back(p2);

    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);
    p1->addTerritory(t4);
    p1->addTerritory(t5);
    p2->conquerTerritory(t3);
    p2->conquerTerritory(t4);

    cout << "\n\nContinent bonus for p1: ";
    cout << map->allContinentsBonus(p1) << endl;
    cout << "Continent bonus for p2: ";
    cout << map->allContinentsBonus(p2) << endl;

    cout << "Player 1 currently owns : " << p1->getNumTerritories() << " territories" << endl;
    cout << "Player 2 currently owns : " << p2->getNumTerritories() << " territories" << endl;

    cout << "\nExecuting reinforcement phase..." << endl;
    game->reinforcementPhase();


//    cout << p1->getNumTerritories() << endl;
//    cout << p2->getNumTerritories() << endl;


//    cout << "Player 1 owned territories:" << endl;
//    for(Territory* t : p1->getTerritories()){
//        cout << *t << endl;
//    }
//
//    cout << "Player 2 owned territories:" << endl;
//    for(Territory* t : p2->getTerritories()){
//        cout << *t << endl;
//    }

//    cout << "Player's orders list:" << endl;
//    p1->issueOrder();
//    cout << *p1->getPlayerOrderList() << endl;
//
//    cout << "Player's hand:" << endl;
//    p1->getHand()->addCard(new BlockadeCard);
//    p1->getHand()->addCard(new BombCard);
//    p1->getHand()->addCard(new AirliftCard);
//    p1->getHand()->addCard(new ReinforcementCard);
//    p1->getHand()->addCard(new DiplomacyCard);
//    cout << *p1->getHand() << endl;
//
//    cout << "\nTerritories to defend:" << endl;
//    for (Territory* t : p1->toDefend()){
//        cout << *t << endl;
//    }
//    cout << "Territories to attack:" << endl;
//    for (Territory* t : p1->toAttack()){
//        cout << *t << endl;
//    }

    // cleanup
    delete p1;
    p1 = nullptr;
}