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
    cout << "Order added. Current list: \n" << *ol << endl;
    ol->add(testAdvance);
    cout << "Order added. Current list: \n" << *ol << endl;
    ol->add(testBomb);
    cout << "Order added. Current list: \n" << *ol << endl;
    ol->add(testBlockade);
    cout << "Order added. Current list: \n" << *ol << endl;
    ol->add(testAirlift);
    cout << "Order added. Current list: \n" << *ol << endl;
    ol->add(testNegotiate);
    cout << "Order added. Current list: \n" << *ol << endl;

    // move orders
    cout << "\n============= Move orders 1 and 3 =============\n" << endl;
    ol->move(1, 3);
    cout << "Orders swapped. Current list: \n" << *ol << endl;
    cout << "\n============= Move orders 4 and 5 =============\n" << endl;
    ol->move(4, 5);
    cout << "Orders swapped. Current list: \n" << *ol << endl;

    // delete orders
    cout << "\n============= Delete order 3 =============\n" << endl;
    ol->remove(3);
    cout << "Order deleted. Current list: \n" << *ol << endl;
    cout << "\n============= Delete order 2 =============\n" << endl;
    ol->remove(2);
    cout << "Order deleted. Current list: \n" << *ol << endl;

    // execute list - invokes validate() and execute() method on each order then delete order in list
    cout << "\n============= Execute list =============\n" << endl;
    ol->executeList();
    cout << "\n=========================================\n" << endl;

    // cleanup
    delete ol;
    ol = NULL;
}