//
// Created by Alice on 2022-09-26.
//
#include "Orders.h"

/**
 * Free function to test Order and OrdersList
 */
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
    cout << "\n============= Add orders =============\n" << endl;
    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);

    // move orders
    cout << "\n============= Move orders 1 and 3 =============\n" << endl;
    ol->move(1, 3);
    cout << "\n============= Move orders 4 and 5 =============\n" << endl;
    ol->move(4, 5);

    // delete orders
    cout << "\n============= Delete order 3 =============\n" << endl;
    ol->remove(3);
    cout << "\n============= Delete order 2 =============\n" << endl;
    ol->remove(2);

    // execute list - invokes validate() and execute() method on each order in list
    cout << "\n============= Execute list =============\n" << endl;
    ol->executeList();
}