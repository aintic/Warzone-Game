#pragma once
#include <iostream>
#include <vector>
#include "../Orders/Orders.h"
#include "../Map/Map.h"
//#include "../Cards/Cards.h"

using namespace std;

class Hand;
//Order class just for testing


class Player{

    public:
        Player();
        Player(int playerID, string name);
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, OrdersList* orders);
        Player(const Player& p); //copy constructor
        ~Player(); //desturctor
        Player& operator=(const Player& p); //assignment operator
        int getPlayerID();
        OrdersList* getPlayerOrderList();
        Hand* getHand();
        string getName();
        vector<Territory*> getTerritories();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder(Player *p);
        void issueOrder(Order* o);
        void addTerritory(Territory* territory);


private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        vector<Territory*> territoriesOwnedByPlayer;
        OrdersList* order_list;
        int reinforcement; // Number of armies in the reinforcement pool
        //PlayerStrategy* ps; // Pointer to a player strategy
        int playerID;
};