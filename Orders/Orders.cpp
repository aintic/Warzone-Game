//
// Created by Alice on 2022-09-26.
//

#include "Orders.h"

using namespace std;

// set constant members for subclasses
const string Deploy::_orderType = "Deploy";
const string Advance::_orderType = "Advance";
const string BombCardOrder::_orderType = "Bomb";
const string BlockadeCardOrder::_orderType = "Blockade";
const string AirliftCardOrder::_orderType = "Airlift";
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
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Order& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Assignment operator for Order
 * @param o - Orders object
 * @return Order object
 */
Order& Order::operator=(const Order& o) {
    Order::operator=(o);
    return *this;
}

/**
 * Default constructor for Deploy
 */
Deploy::Deploy() = default;

Deploy::Deploy(GameEngine* game) {
    this->Attach(game->_observers);
}

/**
 * Default destructor for Deploy
 */
Deploy::~Deploy() = default;

/**
 * Stream insertion operator for Deploy
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Deploy& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string then returns true for a1
 * @return boolean
 */
bool Deploy::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void Deploy::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
    Notify(this);

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

/**
 * Method returning order's effect
 * @return string
 */
string Deploy::orderEffect() const {
    return "Put a certain number of army units on a target territory.";
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
 * Stream insertion operator for Advance
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Advance& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string for a1
 * @return boolean
 */
bool Advance::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void Advance::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Advance::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return Advance - cloned object
 */
Order* Advance::clone() const {
    return new Advance(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string Advance::orderEffect() const {
    return "Move a certain number of army units from one territory (source) to another (target).";
}

/**
 * Default constructor for BombCardOrder
 */
BombCardOrder::BombCardOrder() = default;

/**
 * Default destructor for BombCardOrder
 */
BombCardOrder::~BombCardOrder() = default;

/**
 * Stream insertion operator for Bomb
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const BombCardOrder& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string for a1
 * @return boolean
 */
bool BombCardOrder::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void BombCardOrder::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string BombCardOrder::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return BombCardOrder - cloned object
 */
Order* BombCardOrder::clone() const {
    return new BombCardOrder(*this);
}
/**
 * Method returning order's effect
 * @return string
 */
string BombCardOrder::orderEffect() const {
    return "Destroy half of the army units located on a target territory. (Requires card)";
}

/**
 * Default constructor for BlockadeCardOrder
 */
BlockadeCardOrder::BlockadeCardOrder() = default;

/**
 * Default destructor for BlockadeCardOrder
 */
BlockadeCardOrder::~BlockadeCardOrder() = default;

/**
 * Stream insertion operator for Blockade
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const BlockadeCardOrder& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string for a1
 * @return boolean
 */
bool BlockadeCardOrder::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void BlockadeCardOrder::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string BlockadeCardOrder::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return BlockadeCardOrder - cloned object
 */
Order* BlockadeCardOrder::clone() const {
    return new BlockadeCardOrder(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string BlockadeCardOrder::orderEffect() const {
    return "Triple the number of army units on a target territory and make it neutral. (Requires card)";
}

/**
 * Default constructor for AirliftCardOrder
 */
AirliftCardOrder::AirliftCardOrder() = default;

/**
 * Default destructor for AirliftCardOrder
 */
AirliftCardOrder::~AirliftCardOrder() = default;

/**
 * Stream insertion operator for Airlift
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const AirliftCardOrder& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string for a1
 * @return boolean
 */
bool AirliftCardOrder::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void AirliftCardOrder::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string AirliftCardOrder::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return AirliftCardOrder - cloned object
 */
Order* AirliftCardOrder::clone() const {
    return new AirliftCardOrder(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string AirliftCardOrder::orderEffect() const {
    return "Advance a certain number of army units from one from one territory (source) to another (target). (Requires card)";
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
 * Stream insertion operator for Negotiate
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Negotiate& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate method - prints a string for a1
 * @return boolean
 */
bool Negotiate::validate() const {
    cout << "Validating order. \n";
    return true;
}

/**
 * Execute method - prints order effect if validate returns true
 */
void Negotiate::execute() {
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        cout << orderEffect() << "\n\n";
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Negotiate::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return Negotiate - cloned object
 */
Order* Negotiate::clone() const {
    return new Negotiate(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string Negotiate::orderEffect() const {
    return "Prevent attacks between the current player and another target player until the end of the turn. (Requires card)";
}

/**
 * Default constructor for OrdersList
 */
OrdersList::OrdersList() = default;

/**
 * Destructor for OrdersList
 */
OrdersList::~OrdersList(){
    int size = _ordersList.size();

    for (int i = 0; i < size; i++) {
        delete _ordersList[i];
    }
};

/**
 * Copy constructor for OrdersList - makes deep copy
 * @param ol - OrdersList object
 */
OrdersList::OrdersList(const OrdersList& ol) {
    int size = ol._ordersList.size();

    _ordersList = vector<Order*>(size);
    for (int i = 0; i < size; i++) {
        _ordersList[i] = ol._ordersList[i]->clone();
    }
}

/**
 * Stream insertion operator for OrdersList
 * @param ol - OrdersList object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out, const OrdersList& ol) {
    int size = ol._ordersList.size();
    for (int i = 0; i < size; i++) {
        out << "[ " << *ol._ordersList[i] << " ] \n";
    }
    return out;
}

/**
 * Assignment operator for OrdersList
 * @param ol - OrdersList object
 * @return OrdersList object
 */
OrdersList& OrdersList::operator=(const OrdersList& ol) {
    // check self-assignment
    if (this == &ol)
        return *this;

    // free memory of original orders list
    for (int i = 0; i < _ordersList.size(); i++) {
        delete _ordersList[i];
    }

    int size = ol._ordersList.size();
    // set list size equal to target orders list
    _ordersList = vector<Order*>(size);
    // clone deep copy of target orders list to original orders list
    for (int i = 0; i < size; i++) {
        _ordersList[i] = ol._ordersList[i]->clone();
    }

    return *this;
}

/**
 * Method to add an order to the player's orders' list
 * @param o - order object
 */
void OrdersList::add(Order* o) {
    // add new order to vector
    _ordersList.push_back(o);
}

/**
 * Method to remove an order from the player's orders' list
 * @param pos - an int for the position of the order to be removed
 */
void OrdersList::remove(int pos) {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order in list." << endl;
    else if (pos < 1 || pos > size)
        cout << "Invalid order position." << endl;
    else {
        // delete pointer
        delete _ordersList[pos-1];
        // resize vector
        _ordersList.erase(_ordersList.begin()+pos-1);
    }
}

/**
 * Method to move an order from one position to another in the player's orders' list
 * @param currentPos - an int for current position of the order
 * @param newPos - an int for the new position of the order
 */
void OrdersList::move(int currentPos, int newPos) {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order to move." << endl;
    else if (size == 1)
        cout << "Cannot swap with 1 order in list." << endl;
    else if (currentPos < 1 || newPos < 1 || currentPos > size || newPos > size)
        cout << "Invalid order position." << endl;
    else {
        // temp object storing order at current position
        Order* temp = _ordersList[currentPos-1];
        // move the order at target position to current position
        _ordersList[currentPos-1] = _ordersList[newPos-1];
        // move the order at current position to target position
        _ordersList[newPos-1] = temp;
    }
}

/**
 * Method to execute then remove orders sequentially from player's orders' list
 */
void OrdersList::executeList() {
    int size = _ordersList.size();

    if (size == 0)
        cout << "No order to execute." << endl;
    else {
        // execute each order in vector then delete pointer
        for (int i = 0; i < size; i++) {
            _ordersList[i]->execute();
            delete _ordersList[i];
        }
        // remove all elements from vector (now size 0)
        _ordersList.clear();
        // print end of execution
        cout << "\nExecuted all orders. List is now empty." << endl;
    }
}

//Method to execute a single order
//maybe make it boolean? so if any more orders to execute it returns true
void OrdersList::executeOrder() {
    int size = _ordersList.size();

    _ordersList.front()->execute();
    delete _ordersList.front();
    _ordersList.erase(_ordersList.begin());
    cout << "New size of orderlist : " << size << " -> " << _ordersList.size() << endl;
}


//Make sure that it's never called on empty orderList
Order* OrdersList::getTopOrder() {
//    if(!_ordersList.empty()){
        cout << "Top order : ";
        Order* o = _ordersList.front();
        cout << *o << endl;
        return o;
//    }
}

vector<Order *> OrdersList::getOrderList() {
    return _ordersList;
}

string Order::stringToLog()
{
    return "Order: " + getOrderType();
}
