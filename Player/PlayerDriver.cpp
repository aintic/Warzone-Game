#include "Player.h"
#include "Map.h"


using namespace std;

void testPlayers() {
    string name = "Hongsuk";
    vector<Order*> orders;

    vector<Territory*> territories;
    Hand* hand;
    Player* p1 = new Player(1, name, territories, hand, orders);
    Player* p2 = new Player();


    Territory *t1 = new Territory("t1");
    Territory *t2 = new Territory("t2");
    Territory *t3 = new Territory("t3");


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
    p2->issueOrder("First issue order");
    p2->issueOrder("second issue order");
    p2->issueOrder("3rd issue order");

    cout << "Order list print"  << endl;

    for(Order* order : p2->getPlayerOrderList()){
        cout << order->name << endl;
    }

    //delete all pointers
    delete p1;
    delete p2;
    delete t1;
    delete t2;
    delete t3;

}

//int main(){
//    testPlayers();
//};


