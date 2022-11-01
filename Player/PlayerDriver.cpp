#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"


using namespace std;

bool allTerritoriesOwned(){


}


void testPlayers() {

    Player *p1 = new Player;
    Player *p2 = new Player;
    cout << *p1 << endl;

    vector<string> neighbor = {"t1", "t2", "t3", "t4", "t5"};

    Territory* t1 = new Territory(1,"t1","1",0,0, neighbor);
    Territory* t2 = new Territory(2,"t2","1",1,1, neighbor);
    Territory* t3 = new Territory(3,"t3","2",2,2, neighbor);
    Territory* t4 = new Territory(4,"t4","3",3,3, neighbor);
    Territory* t5 = new Territory(5,"t5","1",4,4, neighbor);


    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);
    p1->addTerritory(t4);
    p1->addTerritory(t5);
    p1->removeTerritory(t1);
    p2->addTerritory(t1);
    cout << p1->getNumTerritories() << endl;
    cout << p2->getNumTerritories() << endl;

    cout << "Player 1 owned territories:" << endl;
    for(Territory* t : p1->getTerritories()){
        cout << *t << endl;
    }

    cout << "Player 2 owned territories:" << endl;
    for(Territory* t : p2->getTerritories()){
        cout << *t << endl;
    }

    cout << "Player's orders list:" << endl;
    p1->issueOrder();
    cout << *p1->getPlayerOrderList() << endl;

    cout << "Player's hand:" << endl;
    p1->getHand()->addCard(new BlockadeCard);
    p1->getHand()->addCard(new BombCard);
    p1->getHand()->addCard(new AirliftCard);
    p1->getHand()->addCard(new ReinforcementCard);
    p1->getHand()->addCard(new DiplomacyCard);
    cout << *p1->getHand() << endl;

    cout << "\nTerritories to defend:" << endl;
    for (Territory* t : p1->toDefend()){
        cout << *t << endl;
    }
    cout << "Territories to attack:" << endl;
    for (Territory* t : p1->toAttack()){
        cout << *t << endl;
    }

    // cleanup
    delete p1;
    p1 = nullptr;
}


