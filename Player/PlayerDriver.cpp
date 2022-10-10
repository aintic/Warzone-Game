#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"


using namespace std;

void testPlayers() {

    Player p1;

    vector<string> neighbor = {"t1", "t2", "t3", "t4", "t5"};
    p1.addTerritory(new Territory(1,"t1","Territory1",0,0, neighbor));
    p1.addTerritory(new Territory(2,"t2","Territory2",1,1, neighbor));
    p1.addTerritory(new Territory(3,"t3","Territory3",2,2, neighbor));
    p1.addTerritory(new Territory(4,"t4","Territory4",3,3, neighbor));
    p1.addTerritory(new Territory(5,"t5","Territory5",4,4, neighbor));

    cout << "Player's owned territories:" << endl;
    for(Territory* t : p1.getTerritories()){
        cout << *t << endl;
    }

    cout << "Player's orders list:" << endl;
    p1.issueOrder();
    p1.issueOrder();
    p1.issueOrder();
    cout << *p1.getPlayerOrderList() << endl;

    cout << "Player's hand:" << endl;
    p1.getHand()->addCard(new BlockadeCard);
    p1.getHand()->addCard(new BombCard);
    p1.getHand()->addCard(new AirliftCard);
    p1.getHand()->addCard(new ReinforcementCard);
    p1.getHand()->addCard(new DiplomacyCard);
    cout << *p1.getHand() << endl;

    cout << "\nTerritories to defend:" << endl;
    for (Territory* t : p1.toDefend()){
        cout << *t << endl;
    }
    cout << "Territories to attack:" << endl;
    for (Territory* t : p1.toAttack()){
        cout << *t << endl;
    }



}


