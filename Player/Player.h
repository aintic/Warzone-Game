#pragma once
#ifndef COMP_345_PLAYER_H
#define COMP_345_PLAYER_H

#endif //COMP_345_PLAYER_H

#include <iostream>
#include <vector>
#include "../Orders/Orders.h"
#include "../Map/Map.h"

using namespace std;

class Hand;
//Order class just for testing


class Player{

    public:
        Player();
        Player(int playerID, string name);
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<OrdersList*> orders);
        Player(const Player& p); //copy constructor
        ~Player(); //desturctor
        Player& operator=(const Player& p); //assignment operator
        int getPlayerID();
        vector<OrdersList*> getPlayerOrderList();
        Hand* getHand();
        string getName();
        vector<Territory*> getTerritories();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder(Player *p);
        void addTerritory(Territory* territory);


private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        vector<Territory*> territoriesOwnedByPlayer;
        vector<OrdersList*> order_list;
        int reinforcement; // Number of armies in the reinforcement pool
        //PlayerStrategy* ps; // Pointer to a player strategy
        int playerID;



};