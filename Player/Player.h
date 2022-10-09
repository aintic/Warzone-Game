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
        Player(int playerID, string name, vector<Territory*> territories, Hand* hand, OrdersList* orders);
        /**
         * copy constructor
         * @param p
         */
        Player(const Player& p);
        /**
         * destructor
         */
        ~Player(); //desturctor
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
         * issueOrder : crates an order object and Player object sets its orderlist
         * @param p
         */
        void issueOrder();
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
        OrdersList* setPlayerOrderList(OrdersList* orders);

private:
        string name;
        Hand* hand;
        vector<Territory*> territories; // List of owned territories
        vector<Territory*> territoriesOwnedByPlayer;
        OrdersList* order_list;
        int playerID;



};