//
// Created by Alice on 2022-09-26.
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Map.h"
#include "GameEngine.h"

class Territory;
class Player;
class GameEngine;
using namespace std;

class Order {
public:
    // constructor
    Order();
    // parametized constructor
    Order(Player *currentPl);
    // destructor
    virtual ~Order() = 0;
    // assignment operator
    Order& operator = (const Order& o);
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Order& o);

    // verifies if order is valid
    virtual bool validate() const = 0;
    // execute order
    virtual void execute() = 0;
    // get order type
    virtual string getOrderType() const = 0;
    // clone order
    virtual Order* clone() const = 0;
    // return order effect string
    virtual string orderEffect() const = 0;

    friend class OrdersList;

protected:
    Player *currentPl;
};

class Deploy : public Order {
public:
    // constructor
    Deploy();
    // parametized constructor
    Deploy(Territory *targetTer, Player *currentPl, int army_units);
    // destructor
    ~Deploy() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Deploy& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order *clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Territory *targetTer;
    int army_units;

};

class Advance : public Order {
public:
    // constructor
    Advance();
    // parametized constructor
    Advance(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units);
    // destructor
    ~Advance() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Advance& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order* clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Territory *targetTer;
    Territory *sourceTer;
    int army_units;
};

class Bomb : public Order {
public:
    //constructor
    Bomb();
    // parametized constructor
    Bomb(Territory *targetTer, Player *currentPl);
    // destructor
    ~Bomb() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Bomb& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order* clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Territory *targetTer;
};

class Blockade : public Order {
public:
    // constructor
    Blockade();
    // parametized constructor
    Blockade(Territory *targetTer, Player *currentPl);
    // destructor
    ~Blockade() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Blockade& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order* clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Territory *targetTer;
};

class Airlift : public Order {
public:
    // constructor
    Airlift();
    // parametized constructor
    Airlift(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units);
    // destructor
    ~Airlift() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Airlift& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order* clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Territory *targetTer;
    Territory *sourceTer;
    int army_units;
};

class Negotiate : public Order {
public:
    //constructor
    Negotiate();
    // parametized constructor
    Negotiate(Player *currentPl, Player *enemyPl);
    // destructor
    ~Negotiate() override;
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const Negotiate& o);
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() override;
    // get order type
    string getOrderType() const override;
    // clone order
    Order* clone() const override;
    // return order effect string
    string orderEffect() const override;

private:
    const static string _orderType;
    Player *enemyPl;
};

class OrdersList {
public:
    // constructor
    OrdersList();
    // copy constructor
    OrdersList(const OrdersList &ol);
    // destructor
    ~OrdersList();
    // assignment operator
    OrdersList& operator = (const OrdersList& ol);
    // stream insertion operator
    friend ostream& operator << (ostream& out, const OrdersList& ol);

    // add order to list
    void add(Order* o);
    // move orders from one position to another
    void move(int currentPos, int newPos);
    // remove an order at specified position
    void remove(int pos);
    // execute then delete orders from list sequentially
    void executeList();

    void executeOrder();
    Order* getTopOrder();
    vector<Order*> getOrderList();

private:
    vector<Order*> _ordersList;
};