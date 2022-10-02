#include "Player.h"
#include "Map.h"


void testPlayers() {
    string name = "Hongsuk";
    vector<Order*> orders;

    vector<Territory*> territories;
    Hand* hand;
    Player* p1 = new Player(1, name, territories, hand, orders);
    cout << p1->getPlayerID() << endl;

    Territory *t1 = new Territory("t1");
    Territory *t2 = new Territory("t2");
    Territory *t3 = new Territory("t3");
    Territory *t4 = new Territory("t4");
    Territory *t5 = new Territory("t5");
    Territory *t6 = new Territory("t6");


    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);

    for(Territory* t : p1->toDefend()){
        cout << t->name << endl;
    }

    //	map<int, Territory*> territories;
}

