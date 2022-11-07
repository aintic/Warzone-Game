//
// Created by Alice on 2022-09-26.
//

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../LoggingObserver/LoggingObserver.h"
#include "../GameEngine/GameEngine.h"

using namespace std;

//class GameEngine;

class Order : public ILoggable, public Subject{
public:
    // constructor
    Order();
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
    string stringToLog();

};

class Deploy : public Order {
public:
    // constructor
    Deploy();

    Deploy(GameEngine* game);
    // destructor
    ~Deploy();
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
    // string for type of order
    const static string _orderType;
};

class Advance : public Order {
public:
    // constructor
    Advance();
    // destructor
    ~Advance();
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
    // string for type of order
    const static string _orderType;
};

class BombCardOrder : public Order {
public:
    //constructor
    BombCardOrder();
    // destructor
    ~BombCardOrder();
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const BombCardOrder& o);

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
    // string for type of order
    const static string _orderType;
};

class BlockadeCardOrder : public Order {
public:
    // constructor
    BlockadeCardOrder();
    // destructor
    ~BlockadeCardOrder();
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const BlockadeCardOrder& o);
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
    // string for type of order
    const static string _orderType;
};

class AirliftCardOrder : public Order {
public:
    // constructor
    AirliftCardOrder();
    // destructor
    ~AirliftCardOrder();
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const AirliftCardOrder& o);
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
    // string for type of order
    const static string _orderType;
};

class Negotiate : public Order {
public:
    //constructor
    Negotiate();
    // destructor
    ~Negotiate();
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
    // string for type of order
    const static string _orderType;
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
    void move(int, int);
    // remove an order at specified position
    void remove(int);
    // execute then delete orders from list sequentially
    void executeList();

    void executeOrder();
    Order* getTopOrder();
    vector<Order*> getOrderList();

private:
    // list of orders
    vector<Order*> _ordersList;
};