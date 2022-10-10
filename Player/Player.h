#pragma once
#include <iostream>
#include <vector>
#include "../Orders/Orders.h"
#include "../Map/Map.h"

using namespace std;

class Hand;

//
//PLAYER CLASS
//
//Purpose: The player class represents a Warzone player who owns a collection of territories and a hand of cards.
//         Each player has a list of orders that he will issue during the game.
//
class Player{

public:
    /**
     * default constructor
     */
    Player();

    /**
     * Player constructor: creates a Player object
     * @param playerID
     * @param name
     */
    Player(int playerID, string name);

    /**
     * Player constructor: creates a Player object
     * @param playerID
     * @param name
     * @param territories
     * @param hand
     * @param orders
     */
    Player(int playerID, string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders);

    /**
     * copy constructor
     * @param p
     */
    Player(const Player& p);

    /**
     * destructor
     */
    ~Player();

    /**
     * assignment operator
     * @param p
     * @return &Player
     */
    Player& operator=(const Player& p);

    /**
     * getters
     * @return
     */
    int getPlayerID();
    OrdersList* getPlayerOrderList();
    Hand* getHand();
    string getName();
    vector<Territory*> getTerritories();

    /**
     * toDefend: return a list of territories to be defended
     * @return vector<Territory*>
     */
    vector<Territory*> toDefend();

    /**
     * toAttack: return a list of territories to be attacked
     * @return vector<Territory*>
     */
    vector<Territory*> toAttack();

    /**
     * issueOrder : creates an order object and Player object sets its orderlist
     * @param p
     */
    void issueOrder();

    /**
     * issueOrder : method for testing purposes to add orders to orderList
     * @param p
     */
    void issueOrder(Order* o);

    /**
     * addTerritory: adds player's territories
     * @param territory
     */
    void addTerritory(Territory* territory);

    /**
     * setters
     * @param orders
     * @return
     */
    void setPlayerOrderList(OrdersList* orders);

    /**
     * setTerritories
     * @return territories that are owned by player
     */
    void setTerritories(vector<Territory*> t);

private:
    string name;
    Hand* hand;
    vector<Territory*> territories; // List of owned territories
    OrdersList* order_list;
    int playerID;
};

/**
 * Stream insertion operator
 */
ostream& operator << (ostream& os, Player& p);