//
// Created by Alice on 2022-09-26.
//

#ifndef COMP_345_ORDERS_H
#define COMP_345_ORDERS_H

#endif //COMP_345_ORDERS_H

#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Order {
public:
    // constructor
    Order();
    // destructor
    virtual ~Order() = 0;
    // assignment operator
    Order& operator = (const Order& o);
    // string insertion operator
    friend ostream& operator << (ostream& out,  const Order& o);

    // verifies if order is valid
    virtual bool validate() const = 0;
    // execute order
    virtual void execute() const = 0;
    // get order type
    virtual string getOrderType() const = 0;
    // clone order
    virtual Order* clone() const = 0;
    // return order effect string
    virtual string orderEffect() const = 0;

    friend class OrdersList;
};

class Deploy : public Order {
public:
    // constructor
    Deploy();
    // destructor
    ~Deploy();
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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

class Bomb : public Order {
public:
    //constructor
    Bomb();
    // destructor
    ~Bomb();
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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

class Blockade : public Order {
public:
    // constructor
    Blockade();
    // destructor
    ~Blockade();
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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

class Airlift : public Order {
public:
    // constructor
    Airlift();
    // destructor
    ~Airlift();
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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
    // verifies if order is valid
    bool validate() const override;
    // execute order
    void execute() const override;
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
    // string insertion operator
    friend ostream& operator << (ostream& out, const OrdersList& ol);

    // add order to list
    void add(Order* o);
    // move orders from one position to another
    void move(int, int);
    // remove an order at specified position
    void remove(int);
    // execute orders in list then delete order from list sequentially
    void executeList();

private:
    // list of orders
    vector<Order*> _ordersList;
};