#include "CardsDriver.h"
#include "Cards.h"
#include <iostream>
using std::cout;
using std::endl;

void testCards(){
    cout << "Initialize deck with 3 cards of each type:"  << endl;

    Deck d;
    cout << d << endl;

    cout << "Create 3 hands and randomly draw 5 cards each:" << endl;

    Hand h1;
    Hand h2;
    Hand h3;

    while(!d.isEmpty()){
        if(!d.isEmpty()){
            cout << "Hand 1 draws: " << *d.draw(h1) << endl;
        }
        if(!d.isEmpty()){
            cout << "Hand 2 draws: " << *d.draw(h2) << endl;
        }
        if(!d.isEmpty()){
            cout << "Hand 3 draws: " << *d.draw(h3) << endl;
        }
    }

    cout << "\nHand 1: " << endl;
    cout << h1 << "\n" << endl;

    cout << "Hand 2: " << endl;
    cout << h2 << "\n" << endl;

    cout << "Hand 3: " << endl;
    cout << h3 << "\n" << endl;

    cout << d << endl;

    cout << "Play all 5 cards in each hand:" << endl;

    for (Card* c : h1.getCards()){
        c->transfer(h1, d, 0);
    }
    for (Card* c : h2.getCards()){
        c->transfer(h2, d, 0);
    }
    for (Card* c : h3.getCards()){
        c->transfer(h3, d, 0);
    }

    cout << "Hand 1: " << endl;
    cout << h1 << endl;

    cout << "Hand 2: " << endl;
    cout << h2  << endl;

    cout << "Hand 3: " << endl;
    cout << h3 << endl;

    cout << d;


}

int main()
{
    testCards();
    return 0;
}
