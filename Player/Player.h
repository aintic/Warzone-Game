#pragma once
#include <iostream>
#include <vector>
#include "PlayerStrategies.h"

#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include <algorithm>

using namespace std;

class Hand;
class Deck;
class GameEngine;
class PlayerStrategy;

//
//PLAYER CLASS
//
//Purpose: The player class represents a Warzone player who owns a collection of territories and a hand of cards.
//         Each player has a list of orders that he will issue during the game.
//
class Player{

protected:
    static int uniqueID;
public:
    Player(); //default constructor
    Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders, GameEngine *game); //parametrized constructor
    Player(string name, GameEngine* game); //player constructor
    Player(const Player& p); //copy constructor
    ~Player(); //destructor
    Player& operator = (const Player& p); //assignment operator
    //Getters and Setters
    int getPlayerID();
    OrdersList* getPlayerOrderList();
    Hand* getHand();
    string getName();
    GameEngine* getGame();
    vector<Territory*> getTerritories();
    int getNumTerritories();
    int getReinforcementPool();
    void setGame(GameEngine* game);
    void setPlayerOrderList(OrdersList* orders);
    void setTerritories(vector<Territory*> t);
    void setReinforcementPool(int armies);
    void setIssuableReinforcementPool(int armies);
    void setAdvanceAttackOrdersIssued(int numOrders);
    void setAdvanceDefendOrdersIssued(int numOrders);
    void setIsDoneIssuingOrders(bool b);
    bool getIsDoneIssuingOrders();
    int getIssuableReinforcementPool() const;
    int getAdvanceAttackOrdersIssued() const;
    int getAdvanceDefendOrdersIssued() const;
    const vector<int> &getFriendlyList() const;
    void addOrder(Order *o);

    vector<Territory*> toDefend(); //player territories to defend
    vector<Territory*> toAttack(); //player territories to attack
    Territory* strongestOwnedNeighbor(Territory* territory);
    void issueOrder(); //creates order object and adds to list of orders
    void conquerTerritory(Territory* t);
    void neutralConquerTerritory(Territory* t);
    void addTerritory(Territory* territory); //adds player's territories ?
    void removeTerritory(Territory* territory);
    friend ostream& operator << (ostream& os, Player& p); //stream insertion operator

    // methods to manipulate friendly players
    // a player is friendly if there was a Negotiate order executed with them during this turn
    bool isFriendly(int playerID); // check if a player is friendly
    void addFriendly(int playerID);
    void resetFriendlyList();

    // method to check whether a player have conquered a territory during this turn
    bool getConquerer();
    void resetConquerer();

    // methods to manipulate the player's strategy (getter and setter)
    PlayerStrategy* getStrategy();
    void setStrategy(PlayerStrategy* strategy);

private:
    PlayerStrategy* ps;
    string name;
    Hand* hand;
    vector<Territory*> territories; //list of owned territories
    OrdersList* order_list; //list of current orders
    int playerID; //unique player ID
    int reinforcementPool;
    int issuableReinforcementPool; // # of armies that can be used to issue a deploy order
    int advanceAttackOrdersIssued; // # of advance attack orders issued
    int advanceDefendOrdersIssued; // # of advance attack orders issued
    bool isDoneIssuingOrders;
    vector<int> friendlyList; // list of IDs of friendly players
    bool conquerer; // whether the player conquered a territory during this turn
    GameEngine *game;
    PlayerStrategy *strategy;

};
