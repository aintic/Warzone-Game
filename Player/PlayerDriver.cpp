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
    cout << p1->getPlayerID() << endl;
    Player *p2 = new Player("player1", game);
    cout << p2->getPlayerID() << endl;

    //Player *p1 = new Player("Player1", vector<Territory*>& territories, Hand* hand, OrdersList* orders, GameEngine *game);

    //GameEngine* game = new GameEngine;

//    p1->setGame(game);
//    p2->setGame(game);

    vector<string> neighbor1 = {"t2", "t5"}; //removed t3
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

    vector<Territory*> neighbors1 = {t2, t5}; //removed t3
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
    //cout << *map << endl;

    //Linking map and players to gameEngine
    game->map = map;
    game->players.push_back(p1);
    game->players.push_back(p2);


//    cout << *game->players[0] << endl;
//    cout << *game->players[1] << endl;
//    cout << *game->players.at(0) << endl;
//    cout << *game->players.at(1) << endl;
//    cout << game->players.size() << endl;
//
//    delete p1;
//    cout << "deleting p1..." << endl;
//
//    cout << *game->players[0] << endl;
//    cout << *game->players[1] << endl;
//    cout << game->players.size() << endl;





    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);
    p1->addTerritory(t4);
    p1->addTerritory(t5);
    p2->conquerTerritory(t3);
    p2->conquerTerritory(t4);

    cout << *game->getDeck() << endl;

    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);

    cout << *game->getDeck() << endl;

    cout << "\n\nContinent bonus for p1: ";
    cout << map->allContinentsBonus(p1) << endl;
    cout << "Continent bonus for p2: ";
    cout << map->allContinentsBonus(p2) << endl;

    cout << "Player 1 currently owns : " << p1->getNumTerritories() << " territories" << endl;
    cout << "Player 2 currently owns : " << p2->getNumTerritories() << " territories" << endl;

    t1->set_army_units(10);
    t2->set_army_units(2);
    t3->set_army_units(9);
    t4->set_army_units(7);
    t5->set_army_units(4);


//    cout << *map << endl;
//    cout << *game->players[0] << endl;
//    cout << *game->players[1] << endl;
//    cout << *game->players.at(0) << endl;
//    cout << *game->players.at(1) << endl;
//    cout << game->players.size() << endl;
//
//    delete p1;
//    cout << "deleting p1..." << endl;
//
//    cout << *map << endl;
//
//    cout << *game->players[0] << endl;
//    cout << *game->players[1] << endl;
//    cout << game->players.size() << endl;

    //cout << "Strongest owned neighbor" << endl;
    //cout << *p2->strongestOwnedNeighbor(t1);
    //cout << *p2->strongestOwnedNeighbor(t2);
    //cout << *p1->strongestOwnedNeighbor(t3);
    //cout << *p1->strongestOwnedNeighbor(t4);
    //cout << *p2->strongestOwnedNeighbor(t5);



    game->mainGameLoop();
    cout << "HERE" << endl;







//    cout << "\nExecuting reinforcement phase..." << endl;
//    game->reinforcementPhase();
//
//    game->issueOrderPhase();
//
//    for(Player* p : game->players){
//        cout << "Player " << p->getPlayerID() << " issued orders: " << endl;
//        cout << p->getPlayerOrderList()[0] << endl;
//    }
//
//    game->executeOrdersPhase();



//    OrdersList* ol = new OrdersList;
//    Order* testDeploy = new Deploy;
//    Order* testAdvance = new Advance;
//    Order* testAdvance2 = new Advance;
//    Order* testBomb = new BombCardOrder;
//    Order* testBlockade = new BlockadeCardOrder;
//    Order* testAirlift = new AirliftCardOrder;
//    Order* testNegotiate = new Negotiate;
//
//    // add orders
//    ol->add(testDeploy);
//    ol->add(testAdvance);
//    ol->add(testAdvance2);
//    ol->add(testBlockade);
//    ol->add(testBomb);
//
//    OrdersList* ol2 = new OrdersList;
//    Order* testDeploy2 = new Deploy;
//    Order* testDeploy3 = new Deploy;
//    Order* testDeploy4 = new Deploy;
//    Order* testBomb2 = new BombCardOrder;
//
//    ol2->add(testDeploy2);
//    ol2->add(testDeploy3);
//    ol2->add(testDeploy4);
//    ol2->add(testAirlift);
//    ol2->add(testNegotiate);
//    ol2->add(testBomb2);
//
//
//    p1->setPlayerOrderList(ol);
//    p2->setPlayerOrderList(ol2);


    //game->mainGameLoop();
    //game->executeOrdersPhase();





//    cout << *p1->getPlayerOrderList()->getTopOrder() << endl;
//    cout << *p1->getPlayerOrderList() << endl;
//    //cout << *p2->getPlayerOrderList()->getTopOrder() << endl;
//    OrdersList ord = *p2->getPlayerOrderList();
//    cout << ord << endl;
//
//
//    cout << *game->players[0] << endl;
//    cout << *game->players[1] << endl;
//    vector<Player*> copied;
//    copied = game->players;
//    cout << *copied[0] << endl;
//    cout << *copied[1] << endl;
//    copied.pop_back();
//
//    for(int i=0;i<copied.size();i++){
//        cout << *copied[i] << endl;
//    }
//
//    for(int i=0;i<game->players.size();i++){
//        cout << *game->players[i] << endl;
//    }


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
    //delete p1;
    //p1 = nullptr;
}