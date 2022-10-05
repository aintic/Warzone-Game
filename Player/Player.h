#pragma once
#ifndef COMP_345_PLAYER_H
#define COMP_345_PLAYER_H

#endif //COMP_345_PLAYER_H

#include <iostream>
#include <vector>
#include "../Map/Map.h"

using namespace std;

class Hand;
//class Territory;
//Order class just for testing
class Order{
    public:
        Order(string name);

    string name;
};

class Player{

    public:
        Player();
        Player(int playerID, string name);
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<Order*> orders);
        Player(const Player& p); //copy constructor
        ~Player(); //desturctor
        Player& operator=(const Player& p); //assignment operator
        int getPlayerID();
        vector<Order*> getPlayerOrderList();
        Hand* getHand();
        string getName();
        vector<Territory*> getTerritories();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder(string order);
        void addTerritory(Territory* territory);


private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        vector<Territory*> territoriesOwnedByPlayer;
        vector<Order*> order_list;
        int reinforcement; // Number of armies in the reinforcement pool
        //PlayerStrategy* ps; // Pointer to a player strategy
        int playerID;



};