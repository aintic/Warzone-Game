//
// Created by Alice on 2022-09-26.
//

#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "GameEngine.h"

using namespace std;

// set constant members for subclasses
const string Deploy::_orderType = "Deploy";
const string Advance::_orderType = "Advance";
const string Bomb::_orderType = "Bomb";
const string Blockade::_orderType = "Blockade";
const string Airlift::_orderType = "Airlift";
const string Negotiate::_orderType = "Negotiate";

/**
 * Default constructor for Order
 */
Order::Order() {
    this->currentPl = nullptr;
};

/**
 * Parametized constructor for Order
 */
 Order::Order(Player *currentPl) {
    this->currentPl = currentPl;
}

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
    Order::operator = (o);
    return *this;
}

/**
 * Default constructor for Deploy
 */
Deploy::Deploy() : Order() {
    this->targetTer = nullptr;
    this->army_units = 0;
};

/**
 * Parametized constructor for Deploy
 */
Deploy::Deploy(Territory *targetTer, Player *currentPl, int army_units) : Order(currentPl) {
    this->targetTer = targetTer;
    this->army_units = army_units;
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
 * Validate Deploy
 * @return boolean
 */
bool Deploy::validate() const {
    cout << "Validating " << *this << " order. \n";
    // return false, if the target territory doesn't belong to current player
    if (targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "You cannot deploy to territories you don't own." << endl;
        return false;
    }
    // return false, if # army units to deploy > # army units available in reinforcement pool
    else if (army_units > currentPl->getReinforcementPool()) {
        cout << "Not enough army units in your reinforcement pool." << endl;
        return false;
    }
    // return true for valid order
    else {
        cout << "Order validated." << endl;
        return true;
    }
}

/**
 * Execute Deploy
 */
void Deploy::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Executing " << *this << " order. \n" << endl;
        // take army units from reinforcement pool
        currentPl->setReinforcementPool(currentPl->getReinforcementPool() - army_units);
        // move army units to target territory
        targetTer->set_army_units(targetTer->get_army_units() + army_units);
        cout << *this << " order executed. \n" << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed.\n" << endl;
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
Advance::Advance() : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
};

/**
 * Parametized constructor for Advance
 */
Advance::Advance(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units) : Order(currentPl) {
    this->sourceTer = sourceTer;
    this->targetTer = targetTer;
    this->army_units = army_units;
}

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
 * Validate Advance
 * @return boolean
 */
bool Advance::validate() const {
    cout << "Validating order. \n";
    // return false, if source territory doesn't belong to current player
    if (sourceTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "You must advance from a territory you own." << endl;
        return false;
    }
    // return false, if # army units to advance exceeds the amount available in source territory
    else if (army_units > sourceTer->get_army_units()) {
        cout << "Not enough army units in source territory to advance." << endl;
        return false;
    }
    // return false, if the # of army units to advance is less than 1
    else if (army_units < 1) {
        cout << "Cannot advance less than 1 army unit." << endl;
        return false;
    }
    // return false, if the target territory belongs to a friendly player
    else if (currentPl->isFriendly(targetTer->get_owner()->getPlayerID())) {
        cout << "You cannot attack this player until next turn." << endl;
        return false;
    }
    else {
        // check if the target territory is adjacent to source territory
        vector<Territory*> neighbors = sourceTer->get_neighbours();
            for (Territory *neighbor : neighbors) {
                if (neighbor->get_id() == targetTer->get_id()) {
                    // return true, target territory IS adjacent
                    cout << "Order validated." << endl;
                    return true;
                }
            }
        // return false, target territory IS NOT adjacent
        return false;
    }
}

/**
 * Execute Advance
 */
void Advance::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        // if both source and target territories belong to the current player (checked source territory in validate())
        if (targetTer->get_owner()->getPlayerID() == currentPl->getPlayerID()) {
            // take army units from source territory
            sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
            // move army units to target territory
            targetTer->set_army_units(targetTer->get_army_units() + army_units);
        }
        // if target territory belongs to enemy player and has 0 army units
        else if (targetTer->get_army_units() == 0) {
            // take army units from source territory
            sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
            cout << "You have conquered this territory!\n" << endl;
            // current player gains target territory, enemy player loses it
            // army units get added to target territory
            currentPl->conquerTerritory(targetTer);
            targetTer->set_army_units(army_units);
        }
        // if target territory belongs to enemy player and has >0 army units
        else {
            // take army units from source territory
            sourceTer->set_army_units(sourceTer->get_army_units() - army_units);

            // initialize random seed and attack/defend variables
            srand (time(NULL));
            int attack = 0;
            int defend = 0;

            // determine # of army units that attacks successfully
            for (int i = 1; i <= army_units; i++) {
                if ((rand() % 100 + 1) <= 60) {
                    attack++;
                }
            }
            // determine # of army units that defends successfully
            for (int i = 1; i <= targetTer->get_army_units(); i++) {
                if ((rand() % 100 + 1) <= 70) {
                    defend++;
                }
            }

            int survivingAttackers = army_units - defend;
            int survivingDefenders = targetTer->get_army_units() - attack;

            // ensure no negative values in case of extreme scenarios
            if(survivingAttackers < 0) {
                survivingAttackers = 0;
            }
            if (survivingDefenders < 0) {
                survivingDefenders = 0;
            }

            // if current player conquers the territory
            if (survivingAttackers > 0 && survivingDefenders == 0) {
                cout << "You have conquered this territory!\n" << endl;
                // current player gains target territory, enemy player loses it
                // surviving army units get added to target territory
                currentPl->conquerTerritory(targetTer);
                targetTer->set_army_units(survivingAttackers);
            }
            // if current player cannot conquer territory
            else {
                cout << "You could not conquer this territory.\n" << endl;
                // move surviving army units back to source territory
                // reduce army units in target territory to surviving defenders
                sourceTer->set_army_units(sourceTer->get_army_units() + survivingAttackers);
                targetTer->set_army_units(survivingDefenders);
            }
        }
        cout << *this << " order executed. \n" << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed.\n" << endl;
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
 * Default constructor for Bomb
 */
Bomb::Bomb() : Order() {
    this->targetTer = nullptr;
};

/**
 * Parametized constructor for Bomb
 */
Bomb::Bomb(Territory *targetTer, Player *currentPl) : Order(currentPl) {
    this->targetTer = targetTer;
}

/**
 * Default destructor for Bomb
 */
Bomb::~Bomb() = default;

/**
 * Stream insertion operator for Bomb
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Bomb& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate Bomb
 * @return boolean
 */
bool Bomb::validate() const {
    cout << "Validating " << *this << " order. \n";
    // return false, if the target territory belongs to current player
    if (targetTer->get_owner()->getPlayerID() == currentPl->getPlayerID()) {
        cout << "You cannot bomb your own territory." << endl;
        return false;
    }
    // return false, if the target territory belongs to a friendly player
    else if (currentPl->isFriendly(targetTer->get_owner()->getPlayerID())) {
        cout << "You cannot attack this player until next turn." << endl;
        return false;
    }
    // return false, if the target territory has no army unit
    else if (targetTer->get_army_units() == 0) {
        cout << "There is no army to bomb." << endl;
        return false;
    }
    // if none of the above,
    else {
        // check if the target territory is adjacent to one of the territories owned by current player
        vector<Territory*> ownedTers = currentPl->getTerritories();
        for (Territory *ownedTer : ownedTers) {
            vector<Territory*> neighbors = ownedTer->get_neighbours();
            for (Territory *neighbor : neighbors) {
                if (neighbor->get_id() == targetTer->get_id()) {
                    // return true, target territory IS adjacent
                    cout << "Order validated." << endl;
                    return true;
                }
            }
        }
        // return false, target territory IS NOT adjacent
        return false;
    }
}

/**
 * Execute Bomb
 */
void Bomb::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Executing " << *this << " order. \n" << endl;
        // halve the army units in target territory
        targetTer->set_army_units(targetTer->get_army_units() / 2);
        cout << *this << " order executed. \n" << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed.\n" << endl;
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Bomb::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return BombCardOrder - cloned object
 */
Order* Bomb::clone() const {
    return new Bomb(*this);
}
/**
 * Method returning order's effect
 * @return string
 */
string Bomb::orderEffect() const {
    return "Destroy half of the army units located on a target territory. (Requires card)";
}

/**
 * Default constructor for Blockade
 */
Blockade::Blockade() : Order() {
    this->targetTer = nullptr;
};

/**
 * Parametized constructor for Blockade
 */
Blockade::Blockade(Territory *targetTer, Player *currentPl) : Order(currentPl) {
    this->targetTer = targetTer;
}
/**
 * Default destructor for Blockade
 */
Blockade::~Blockade() = default;

/**
 * Stream insertion operator for Blockade
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Blockade& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate Blockade
 * @return boolean
 */
bool Blockade::validate() const {
    cout << "Validating order. \n";
    // return false, if target territory doesn't belong to current player
    if (targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "Cannot blockade territories you don't own." << endl;
        return false;
    }
    // return true if order is valid
    else {
        cout << "Order validated." << endl;
        return true;
    }
}

/**
 * Execute Blockade
 */
void Blockade::execute() {
    // if order is valid
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        // double the army units in target territory
        targetTer->set_army_units(targetTer->get_army_units() * 2);

        // get the list of players from the game engine
        vector<Player*> players = game->getPlayers();
        for (Player *p : players) {
            // if there's already a player called Neutral, assign the target territory to them and exit
            if (p->getName().compare("Neutral") == 0) {
                p->addTerritory(targetTer);
                cout << *this << " order executed. \n" << endl;
                return;
            }
        }
        // create player called Neutral if there isn't one, add to players list
        // and assign target territory to them
        Player *neutral = new Player("Neutral");
        neutral->addTerritory(targetTer);
        players.push_back(neutral);
        cout << *this << " order executed. \n" << endl;
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Blockade::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return BlockadeCardOrder - cloned object
 */
Order* Blockade::clone() const {
    return new Blockade(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string Blockade::orderEffect() const {
    return "Triple the number of army units on a target territory and make it neutral. (Requires card)";
}

/**
 * Default constructor for Airlift
 */
Airlift::Airlift() : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
};

/**
 * Parametized constructor for Airlift
 */
Airlift::Airlift(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units) : Order(currentPl) {
    this->sourceTer = sourceTer;
    this->targetTer = targetTer;
    this->army_units = army_units;
}

/**
 * Default destructor for Airlift
 */
Airlift::~Airlift() = default;

/**
 * Stream insertion operator for Airlift
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Airlift& o) {
    out << o.getOrderType();
    return out;
}

/**
 * Validate Airlift
 * @return boolean
 */
bool Airlift::validate() const {
    cout << "Validating order. \n";
    // return false, if either the source or target territory do not belong to current player
    if (sourceTer->get_owner()->getPlayerID() != currentPl->getPlayerID() || targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID() ) {
        cout << "You can only airlift between territories you own." << endl;
        return false;
    }
    // return false if # army units requested for airlift > # army units in source territory
    else if (army_units > sourceTer->get_army_units()) {
        cout << "Not enough army units in source territory." << endl;
        return false;
    }
    // return false if the # requested army units is less than 1
    else if (army_units < 1) {
        cout << "Cannot airlift less than 1 army unit." << endl;
        return false;
    }
    // return true for valid order
    else {
        cout << "Order validated." << endl;
        return true;
    }
}

/**
 * Execute Airlift
 */
void Airlift::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        // take army units from source territory
        sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
        // move army units to target territory
        targetTer->set_army_units(targetTer->get_army_units() + army_units);
        cout << *this << " order executed. \n" << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed.\n" << endl;
    }
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Airlift::getOrderType() const {
    return _orderType;
}

/**
 * Clone method - invokes default copy constructor since there is no object data member
 * @return AirliftCardOrder - cloned object
 */
Order* Airlift::clone() const {
    return new Airlift(*this);
}

/**
 * Method returning order's effect
 * @return string
 */
string Airlift::orderEffect() const {
    return "Advance a certain number of army units from one from one territory (source) to another (target). (Requires card)";
}

/**
 * Default constructor for Negotiate
 */
Negotiate::Negotiate() : Order() {
    this->enemyPl = nullptr;
};

/**
 * Parametized constructor for Negotiate
 */
Negotiate::Negotiate(Player *currentPl, Player *enemyPl) : Order(currentPl) {
    this->enemyPl = enemyPl;
}

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
 * Validate Negotiate
 * @return boolean
 */
bool Negotiate::validate() const {
    cout << "Validating order. \n";
    // return false, if the enemy player is also the current player
    if (enemyPl->getPlayerID() == currentPl->getPlayerID()) {
        cout << "You cannot negotiate with yourself." << endl;
        return false;
    }
    // return false, if the enemy player is already a friendly player
    else if (currentPl->isFriendly(enemyPl->getPlayerID())) {
        cout << "You already negotiated with this player." << endl;
        return false;
    }
    // return true for valid order
    else {
        cout << "Order validated." << endl;
        return true;
    }
}

/**
 * Execute Negotiate
 */
void Negotiate::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Executing " << *this << " order. \n";
        // add each player to the other player's friendly list
        currentPl->addFriendly(enemyPl->getPlayerID());
        enemyPl->addFriendly(currentPl->getPlayerID());
        cout << *this << " order executed. \n" << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed.\n" << endl;
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
    // clone deep copy of target orders list
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
        // delete object
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
        // temp pointer to order at current position
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
        // execute each order in vector then delete order
        for (int i = 0; i < size; i++) {
            _ordersList[i]->execute();
            delete _ordersList[i];
        }
        // empty vector of all entries (delete the pointers)
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