#include "CardsDriver.h"
#include "Cards.h"
#include "../Player/Player.h"
#include <iostream>
using std::cout;
using std::endl;

void testCards(){
    cout << "Initialize deck with 3 cards of each type:"  << endl;

    Deck d;
    cout << d << endl;

    cout << "Create 3 players and randomly draw 5 cards each:" << endl;

    Player p1;
    Player p2;
    Player p3;

    while(!d.isEmpty()){
        if(!d.isEmpty()){
            cout << "Player 1 draws: " << *d.draw(p1) << endl;
        }
        if(!d.isEmpty()){
            cout << "Player 2 draws: " << *d.draw(p2) << endl;
        }
        if(!d.isEmpty()){
            cout << "Player 3 draws: " << *d.draw(p3) << endl;
        }
    }

    cout << "\nPlayer 1 Hand: " << endl;
    cout << *p1.getHand() << "\n" << endl;

    cout << "Player 2 Hand: " << endl;
    cout << *p2.getHand() << "\n" << endl;

    cout << "Player 3 Hand: " << endl;
    cout << *p3.getHand() << "\n" << endl;

    cout << d << endl;

    cout << "Play all 5 cards in each player's hand:" << endl;

    for (Card* c : p1.getHand()->getCards()){
        p1.issueOrder(p1.getHand()->play(d, 0));
    }
    for (Card* c : p2.getHand()->getCards()){
        p2.issueOrder(p2.getHand()->play(d, 0));
    }
    for (Card* c : p3.getHand()->getCards()){
        p3.issueOrder(p3.getHand()->play(d, 0));
    }



    cout << "Player 1 Hand: " << endl;
    cout << *p1.getHand() << endl;

    cout << "Player 2 Hand: " << endl;
    cout << *p2.getHand()  << endl;

    cout << "Player 3 Hand: " << endl;
    cout << *p3.getHand() << endl;

    cout << "\nPlayer 1 Orders List:" << endl;
    cout << *p1.getPlayerOrderList();
    cout << "\nPlayer 2 Orders List:" << endl;
    cout << *p2.getPlayerOrderList();
    cout << "\nPlayer 3 Orders List:" << endl;
    cout << *p3.getPlayerOrderList();

    cout << "\n"<< d;
}

//int main()
//{
//    testCards();
//    return 0;
//}
