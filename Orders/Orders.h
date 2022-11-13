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
#include "../LoggingObserver/LoggingObserver.h"

class Territory;
class Player;
class GameEngine;


using namespace std;

using namespace std;

//class GameEngine;

class Order : public ILoggable, public Subject{
public:
    // constructor
    Order();
    // parametized constructor
    Order(Player *currentPl, GameEngine *game);
    // destructor
    virtual ~Order() = 0;
    // copy constructor
    Order(const Order &o);
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

    friend class OrdersList;
    string stringToLog();


protected:
    Player *currentPl;
    GameEngine *game;
};

class Deploy : public Order {
public:
    // constructor
    Deploy();

    Deploy(GameEngine* game);
    // parametized constructor
    Deploy(Territory *targetTer, Player *currentPl, int army_units, GameEngine *game);
    // destructor
    ~Deploy() override;
    // copy constructor
    Deploy(const Deploy &o);
    // assignment operator
    Deploy& operator = (const Deploy& o);
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

private:
    const static string orderType;
    Territory *targetTer;
    int army_units;
};

class Advance : public Order {
public:
    // constructor
    Advance();

    Advance(GameEngine* game);

    // parametized constructor
    Advance(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units, GameEngine *game);
    // destructor
    ~Advance() override;
    // copy constructor
    Advance(const Advance &o);
    // assignment operator
    Advance& operator = (const Advance& o);
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

private:
    const static string orderType;
    Territory *targetTer;
    Territory *sourceTer;
    int army_units;
};

class Bomb : public Order {
public:
    //constructor
    Bomb();

    Bomb(GameEngine* game);
    // parametized constructor
    Bomb(Territory *targetTer, Player *currentPl, GameEngine *game);
    // destructor
    ~Bomb() override;
    // copy constructor
    Bomb(const Bomb &o);
    // assignment operator
    Bomb& operator = (const Bomb& o);
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

private:
    const static string orderType;
    Territory *targetTer;
};

class Blockade : public Order {
public:
    // constructor
    Blockade();

    Blockade(GameEngine* game);
    // parametized constructor
    Blockade(Territory *targetTer, Player *currentPl, GameEngine *game);
    // destructor
    ~Blockade() override;
    // copy constructor
    Blockade(const Blockade &o);
    // assignment operator
    Blockade& operator = (const Blockade& o);
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

private:
    const static string orderType;
    Territory *targetTer;
};

class Airlift : public Order {
public:
    // constructor
    Airlift();

    Airlift(GameEngine* game);
    // parametized constructor
    Airlift(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units, GameEngine *game);
    // destructor
    ~Airlift() override;
    // copy constructor
    Airlift(const Airlift &o);
    // assignment operator
    Airlift& operator = (const Airlift& o);
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

private:
    const static string orderType;
    Territory *targetTer;
    Territory *sourceTer;
    int army_units;
};

class Negotiate : public Order {
public:
    //constructor
    Negotiate();

    Negotiate(GameEngine* game);
    // parametized constructor
    Negotiate(Player *currentPl, Player *enemyPl, GameEngine *game);
    // destructor
    ~Negotiate() override;
    // copy constructor
    Negotiate(const Negotiate &o);
    // assignment operator
    Negotiate& operator = (const Negotiate& o);
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

private:
    const static string orderType;
    Player *enemyPl;
};

class OrdersList : public ILoggable, public Subject{
public:
    // constructor
    OrdersList();

    OrdersList(GameEngine* game);
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
    string stringToLog();
    Order* getOrder(int pos) const;

private:
    // list of orders
        private:
    vector<Order*> _ordersList;
};