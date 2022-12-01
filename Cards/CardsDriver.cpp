#include "CardsDriver.h"
#include "Cards.h"
#include "../Player/Player.h"
#include <iostream>
using std::cout;
using std::endl;

//void testCards(){
///**
//* Initialize Deck with 3 cards of each type
//*/
//    cout << "Initialize deck with 3 cards of each type:"  << endl;
//
//    Deck* d = new Deck;
//    cout << *d << endl; // print deck
///**
//* Create 3 players
//*/
//    cout << "Create 3 players and randomly draw 5 cards each:" << endl;
//
//    Player *p1 = new Player;
//    Player *p2 = new Player;
//    Player *p3 = new Player;
///**
//* Each player draws 3 cards from the deck
//*/
//    while(!d->isEmpty()){
//        if(!d->isEmpty()){
//            cout << "Player 1 draws: " << *d->draw(*p1) << endl;
//        }
//        if(!d->isEmpty()){
//            cout << "Player 2 draws: " << *d->draw(*p2) << endl;
//        }
//        if(!d->isEmpty()){
//            cout << "Player 3 draws: " << *d->draw(*p3) << endl;
//        }
//    }
//
///**
//* Display cards in each player's hand
//*/
//    cout << "\nPlayer 1 Hand: " << endl;
//    cout << *p1->getHand() << "\n" << endl;
//
//    cout << "Player 2 Hand: " << endl;
//    cout << *p2->getHand() << "\n" << endl;
//
//    cout << "Player 3 Hand: " << endl;
//    cout << *p3->getHand() << "\n" << endl;
//
///**
//* Display contents of now empty deck
//*/
//    cout << *d << endl;
//
///**
//* Play all 5 cards in each player's hand
//*/
//    cout << "Play all 5 cards in each player's hand:" << endl;
//
//    for (Card* c : p1->getHand()->getCards()){
//        p1->getHand()->play(*d, p1, 0);
//    }
//    for (Card* c : p2->getHand()->getCards()){
//        p2->getHand()->play(*d, p2, 0);
//    }
//    for (Card* c : p3->getHand()->getCards()){
//        p3->getHand()->play(*d, p3, 0);
//    }
//
//
///**
//* Display contents of each player's now empty hand
//*/
//    cout << "Player 1 Hand: " << endl;
//    cout << *p1->getHand() << endl;
//
//    cout << "Player 2 Hand: " << endl;
//    cout << *p2->getHand()  << endl;
//
//    cout << "Player 3 Hand: " << endl;
//    cout << *p3->getHand() << endl;
//
///**
//* Display each player's orders list
//*/
//    cout << "\nPlayer 1 Orders List:" << endl;
//    cout << *p1->getPlayerOrderList();
//    cout << "\nPlayer 2 Orders List:" << endl;
//    cout << *p2->getPlayerOrderList();
//    cout << "\nPlayer 3 Orders List:" << endl;
//    cout << *p3->getPlayerOrderList();
//
///**
//* Display now full deck
//*/
//    cout << "\n"<< *d;
//
//    // cleanup
//    delete d;
//    d = NULL;
//    delete p1; delete p2; delete p3;
//    p1 = NULL; p2 = NULL; p3 = NULL;
//}

