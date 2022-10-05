//
// Created by Alice on 2022-09-26.
//
#include "Orders.h"

void testOrdersList() {
    // create new orders' list and one order of each kind
    OrdersList* ol = new OrdersList;
    Order* testDeploy = new Deploy;
    Order* testAdvance = new Advance;
    Order* testBomb = new Bomb;
    Order* testBlockade = new Blockade;
    Order* testAirlift = new Airlift;
    Order* testNegotiate = new Negotiate;

    // add orders
    cout << "\nAdd orders.\n" << endl;
    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);

    // move orders
    cout << "\nMove orders 1 and 3.\n" << endl;
    ol->move(1, 3);
    cout << "\nMove orders 4 and 5.\n" << endl;
    ol->move(4, 5);

    // delete orders
    cout << "\nDelete order 3.\n" << endl;
    ol->remove(3);
    cout << "\nDelete order 2.\n" << endl;
    ol->remove(3);

    // execute list - invoke validate() and execute() method on each order in list
    cout << "\nExecute list:\n" << endl;
    ol->executeList();
}