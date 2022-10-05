#include "Player.h"
#include "Map.h"
#include "../Orders/Orders.h"


using namespace std;

void testPlayers() {

    cout << "Executing testPlayers method" << endl;

    string name = "Hongsuk";
    vector<OrdersList*> orders;

    vector<Territory*> territories;
    Hand* hand;
    Player* p1 = new Player(1, name, territories, hand, orders);
    Player* p2 = new Player();
    vector<string> test;


    Territory *t1 = new Territory(1, "t1", "test", 1,2,test);
    Territory *t2 = new Territory(2, "t2", "test", 1,2,test);
    Territory *t3 = new Territory(3, "t3", "test", 1,2,test);


    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);

    //Testing toDefend function
    cout << "print countires to be defended" << endl;
    for(Territory* t : p1->toDefend()){
        cout << t->name << endl;
    }


    //Testing toAttack function
    cout << "print countires to be attacked" << endl;
    for(Territory* t : p1->toAttack()){
        cout << t->name << endl;
    }

    //Testing issueOrder function

    p1->issueOrder(p1);






}


