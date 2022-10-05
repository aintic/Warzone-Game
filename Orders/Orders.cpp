//
// Created by Alice on 2022-09-26.
//

/**
 * To do:
 * assignment operators for Orders and OrdersList
 * comments
 */

#include "Orders.h"

using namespace std;

const string Deploy::_orderType = "Deploy";
const string Advance::_orderType = "Advance";
const string Bomb::_orderType = "Bomb";
const string Blockade::_orderType = "Blockade";
const string Airlift::_orderType = "Airlift";
const string Negotiate::_orderType = "Negotiate";

/**
 * Default constructor for Order
 */
Order::Order() = default;

/**
 * Default destructor for Order
 */
 Order::~Order() = default;

/**
 * Stream insertion operator for Order
 */
ostream& operator << (ostream& out,  const Order& o) {
    out << o.orderEffect();
    return out;
}

/**
 * Default constructor for Deploy
 */
Deploy::Deploy() = default;

/**
 * Default destructor for Deploy
 */
Deploy::~Deploy() = default;

/**
 * Validate method - prints a string then returns true for a1
 * @return
 */
bool Deploy::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Deploy::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Deploy::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return Deploy - cloned object
 */
Order* Deploy::clone() const {
    return new Deploy(*this);
}

string Deploy::orderEffect() const {
    return "Deploy order";
}

/**
 * Default constructor for Advance
 */
Advance::Advance() = default;

/**
 * Default destructor for Advance
 */
Advance::~Advance() = default;

/**
 * Validate method - prints a string for a1
 * @return
 */
bool Advance::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Advance::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Advance::getOrderType() const {
    return _orderType;
}

Order* Advance::clone() const {
    return new Advance(*this);
}

string Advance::orderEffect() const {
    return "Advance order";
}

/**
 * Default constructor for Bomb
 */
Bomb::Bomb() = default;

/**
 * Default destructor for Bomb
 */
Bomb::~Bomb() = default;

/**
 * Validate method - prints a string for a1
 * @return
 */
bool Bomb::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Bomb::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Bomb::getOrderType() const {
    return _orderType;
}

Order* Bomb::clone() const {
    return new Bomb(*this);
}

string Bomb::orderEffect() const {
    return "Bomb order";
}

/**
 * Default constructor for Blockade
 */
Blockade::Blockade() = default;

/**
 * Default destructor for Blockade
 */
Blockade::~Blockade() = default;

/**
 * Validate method - prints a string for a1
 * @return
 */
bool Blockade::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Blockade::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Blockade::getOrderType() const {
    return _orderType;
}

Order* Blockade::clone() const {
    return new Blockade(*this);
}

string Blockade::orderEffect() const {
    return "Blockade order";
}

/**
 * Default constructor for Airlift
 */
Airlift::Airlift() = default;

/**
 * Default destructor for Airlift
 */
Airlift::~Airlift() = default;

/**
 * Validate method - prints a string for a1
 * @return
 */
bool Airlift::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Airlift::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Airlift::getOrderType() const {
    return _orderType;
}

Order* Airlift::clone() const {
    return new Airlift(*this);
}

string Airlift::orderEffect() const {
    return "Airlift order";
}

/**
 * Default constructor for Negotiate
 */
Negotiate::Negotiate() = default;

/**
 * Default destructor for Negotiate
 */
Negotiate::~Negotiate() = default;

/**
 * Validate method - prints a string for a1
 * @return
 */
bool Negotiate::validate() const {
    cout << "Validating order \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 * @return
 */
void Negotiate::execute() const {
    if (validate()) {
        cout << "Executing " << orderEffect() << "\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Negotiate::getOrderType() const {
    return _orderType;
}

Order* Negotiate::clone() const {
    return new Negotiate(*this);
}

string Negotiate::orderEffect() const {
    return "Negotiate order";
}

OrdersList::OrdersList() = default;

OrdersList::~OrdersList(){
    int size = _ordersList.size();

    for (int i = 0; i < size; i++) {
        delete _ordersList[i];
    }
};

OrdersList::OrdersList(const OrdersList& ol) {
    int size = ol._ordersList.size();
    _ordersList = vector<Order*>(size);

    for (int i = 0; i < size; i++) {
        _ordersList[i] = ol._ordersList[i]->clone();
    }
}

void OrdersList::add(Order* o) {
        _ordersList.push_back(o);
        cout << "Order added. Current list: \n" << *this << endl;
}

void OrdersList::remove(int pos) {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order in list." << endl;
    else if (pos < 1 || pos > size)
        cout << "Invalid order position." << endl;
    else {
        delete _ordersList[pos-1];
        _ordersList.erase(_ordersList.begin()+pos-1);
        cout << "Order deleted. Current list: \n" << *this <<endl;
    }
}

void OrdersList::move(int currentPos, int newPos) {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order to move." << endl;
    else if (size == 1)
        cout << "Cannot swap with 1 order in list." << endl;
    else if (currentPos < 1 || newPos < 1 || currentPos > size || newPos > size)
        cout << "Invalid order position." << endl;
    else {
        Order* temp = _ordersList[currentPos-1]->clone();
        _ordersList[currentPos-1] = _ordersList[newPos-1]->clone();
        _ordersList[newPos-1] = temp;
        cout << "Orders swapped. Current list: \n" << *this <<endl;
    }
}

void OrdersList::executeList() {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order to execute." << endl;
    else {
        for (int i = 0; i < size; i++) {
            _ordersList[i]->execute();
            delete _ordersList[i];
        }

        _ordersList.clear();
        cout << "\nExecuted all orders. List is now empty." << endl;
    }
}

ostream& operator << (ostream& out, const OrdersList& ol) {
    int size = ol._ordersList.size();

    for (int i = 0; i < size; i++) {

        out << "[ " << ol._ordersList[i]->getOrderType() << " ] \n";
    }

    return out;
}


//OrdersList& OrdersList::operator=(const OrdersList& ol) {

//}