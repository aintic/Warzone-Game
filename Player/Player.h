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
class OrdersList;

class Player{

    public:
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<Order*> orders);
        int getPlayerID();
        vector<Order*> getPlayerOrders();
        Hand* getHand();
        vector<Territory*> getTerritories();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();

private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        OrdersList* ordersList;
        int reinforcement; // Number of armies in the reinforcement pool
        //PlayerStrategy* ps; // Pointer to a player strategy
        int playerID;
        vector<Order*> orders;

};