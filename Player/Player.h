#pragma once
#include <iostream>
#include <vector>
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include <algorithm>

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
    Player(); //default constructor
    Player(string name); //player constructor
    Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders); //parametrized constructor
    Player(const Player& p); //copy constructor
    ~Player(); //destructor
    Player& operator=(const Player& p); //assignment operator
    //Getters and Setters
    int getPlayerID();
    OrdersList* getPlayerOrderList();
    Hand* getHand();
    string getName();
    vector<Territory*> getTerritories();
    int getNumTerritories();
    int getReinforcementPool();
    void setPlayerOrderList(OrdersList* orders);
    void setTerritories(vector<Territory*> t);
    void setReinforcementPool(int armies);
    bool getHasIssueNewOrder() const;
    void setHasIssueNewOrder(bool b);

    vector<Territory*> toDefend(); //player territories to defend
    vector<Territory*> toAttack(); //player territories to attack
    void issueOrder(); //creates order object and adds to list of orders
    void issueOrder(Order* o); //issueOrder for testing purposes with pre-made order
    void conquerTerritory(Territory* t);
    void addTerritory(Territory* territory); //adds player's territories ?
    void removeTerritory(Territory* territory);
    friend ostream& operator << (ostream& os, Player& p); //stream insertion operator

private:
    string name;
    Hand* hand;
    vector<Territory*> territories; //list of owned territories
    OrdersList* order_list; //list of current orders
    static int playerID; //unique player ID
    int reinforcementPool;
    bool hasIssueNewOrder;
};
