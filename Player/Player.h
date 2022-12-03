#pragma once
#include <iostream>
#include <vector>
#include "../Strategy/PlayerStrategies.h"

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
public:
    Player(); //default constructor
    Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders, GameEngine *game); //parametrized constructor
    Player(string name, GameEngine* game); // parametized constructor with only name and game
    Player(const Player& p); //copy constructor
    Player& operator = (const Player& p); //assignment operator
    friend ostream& operator << (ostream& os, Player& p); //stream insertion operator
    ~Player(); //destructor

    // methods
    vector<Territory*> toDefend(); //player territories to defend
    vector<Territory*> toAttack(); //player territories to attack
    Territory* strongestOwnedNeighbor(Territory* territory);
    void issueOrder(); //creates order object and adds to list of orders
    void conquerTerritory(Territory* t); // player takes over a territory from advance order
    void neutralConquerTerritory(Territory* t); // neutral player takes over territory from blockade order
    void addTerritory(Territory* territory); //adds player's territories ?
    void removeTerritory(Territory* territory);
    bool isFriendly(int playerID); // check if a player is friendly
    void addFriendly(int playerID); // add a player to friendly list
    void resetFriendlyList(); // reset friendly list
    void resetConquerer(); // reset conquerer boolean
    void addOrder(Order *o); // add 1 order to orderslist

    // getters
    int getPlayerID() const;
    PlayerStrategy* getStrategy() const;
    GameEngine* getGame() const;
    string getName() const;
    vector<Territory*> getTerritories() const;
    OrdersList* getPlayerOrderList() const;
    Hand* getHand() const;
    int getReinforcementPool() const;
    int getIssuableReinforcementPool() const;
    int getAdvanceAttackOrdersIssued() const;
    int getAdvanceDefendOrdersIssued() const;
    bool getIsDoneIssuingOrders() const;
    vector<int> getFriendlyList() const;
    bool getConquerer() const;
    int getNumTerritories() const;

    // setters
    void setStrategy(PlayerStrategy* strategy);
    void setGame(GameEngine* game);
    void setTerritories(vector<Territory*> t);
    void setPlayerOrderList(OrdersList* orders);
    void setReinforcementPool(int armies);
    void setIssuableReinforcementPool(int armies);
    void setAdvanceAttackOrdersIssued(int numOrders);
    void setAdvanceDefendOrdersIssued(int numOrders);
    void setIsDoneIssuingOrders(bool b);

protected:
    static int uniqueID; // keeps track of # players, ensure each player gets a unique id

private:
    int playerID;
    PlayerStrategy *strategy = nullptr;
    GameEngine *game;
    string name;
    Hand* hand; // contains cards player owns
    vector<Territory*> territories; //list of owned territories
    OrdersList* order_list; //list of current orders
    int reinforcementPool;
    int issuableReinforcementPool; // # of armies that can be used to issue a deploy order
    int advanceAttackOrdersIssued; // # of advance attack orders issued
    int advanceDefendOrdersIssued; // # of advance attack orders issued
    bool isDoneIssuingOrders; // whether player is done issuing orders
    vector<int> friendlyList; // list of IDs of friendly players
    bool conquerer; // whether player conquered a territory during this turn
};
