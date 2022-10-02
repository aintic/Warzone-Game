#include "Player.h"
#include "Map.h"


void testPlayers() {
    string name = "Hongsuk";
    vector<Order*> orders;

    vector<Territory*> territories;
    Hand* hand;
    Player* p1 = new Player(1, name, territories, hand, orders);
    cout << p1->getPlayerID() << endl;



    //	map<int, Territory*> territories;
}

