#pragma once
#ifndef COMP_345_PLAYER_H
#define COMP_345_PLAYER_H

#endif //COMP_345_PLAYER_H

#include <iostream>
#include <vector>
#include "../Map/Map.h"

using namespace std;

class Hand;
class Territory;
class Order;

class Player{

    public:
        Player();
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<Order*> orders);
        int getPlayerID();
        vector<Order*> getPlayerOrderList();
        Hand* getHand();
        string getName();
        vector<Territory*> getTerritories();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder(string order);

private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        vector<Order*> order_list;
        int reinforcement; // Number of armies in the reinforcement pool
        //PlayerStrategy* ps; // Pointer to a player strategy
        int playerID;



};