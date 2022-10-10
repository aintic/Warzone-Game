#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"


using namespace std;

void testPlayers() {

//    cout << "Executing testPlayers method" << endl;
//
//    string name = "Hongsuk";
//    OrdersList* orders;
//
//    vector<Territory*> territories;
//    Hand* hand;
//    Player* p1 = new Player(1, name, territories, hand, orders);
//    Player* p2 = new Player();
//    Player* p3 = new Player(1, name, territories, hand, orders);
//
//    vector<string> test;
//
//
//    Territory *t1 = new Territory(1, "t1", "test", 1,2,test);
//    Territory *t2 = new Territory(2, "t2", "test", 1,2,test);
//    Territory *t3 = new Territory(3, "t3", "test", 1,2,test);
//    Territory *t4 = new Territory(4, "t4", "test", 1,2,test);
//    Territory *t5 = new Territory(5, "t5", "test", 1,2,test);
//
//
//    p1->addTerritory(t1);
//    p1->addTerritory(t2);
//    p1->addTerritory(t3);
//
//    p3->addTerritory(t4);
//    p3->addTerritory(t5);
//
//    //Testing toDefend function
//    cout << "print countires to be defended" << endl;
//    for(Territory* t : p1->toDefend()){
//        cout << t->get_name() << endl;
//    }
//
//
//    //Testing toAttack function
//    cout << "print countires to be attacked" << endl;
//    for(Territory* t : p1->toAttack()){
//        cout << t->get_name() << endl;
//    }
//
//    cout << "Printing countries that the player owns" << endl;
//    for(Territory* t : p3->getTerritoriesownbyplayer()){
//        cout << t->get_name() << endl;
//    }
//
//    //Testing issueOrder function
//    cout << "Printing orders that the player issued" << endl;
//    p1->issueOrder();
//    cout << *(p1->getPlayerOrderList()) << endl;
//
//
//    cout << "Printing a hand of cards that the player owns" << endl;
//
//    BlockadeCard* block = new BlockadeCard();
//    ReinforcementCard* reinforce = new ReinforcementCard();
//    BombCard* b = new BombCard();
//    AirliftCard* a = new AirliftCard();
//    DiplomacyCard* d = new DiplomacyCard();
//
//
//    Hand* h1 = p2->getHand();
//
//    h1->addCard(block);
//    h1->addCard(reinforce);
//    h1->addCard(b);
//    h1->addCard(a);
//    h1->addCard(d);
//
//    for(Card* c : h1->getCards()){
//        cout << c->getCardType() << endl;
//    }
//
//
//    //delete pointers
//    delete p1;
//    delete p2;
//
//
//    //pointed dangling ptr to NULL
//    p1 = NULL;
//    p2 = NULL;

//end

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


