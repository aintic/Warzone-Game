//
// Created by Alice on 2022-09-26.
//

#include "Orders.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../Strategy/PlayerStrategies.h"

using namespace std;

// set constant members for subclasses
const string Deploy::orderType = "Deploy";
const string Advance::orderType = "Advance";
const string Bomb::orderType = "Bomb";
const string Blockade::orderType = "Blockade";
const string Airlift::orderType = "Airlift";
const string Negotiate::orderType = "Negotiate";

// *****************************************************************************************************************
// ORDER
// *****************************************************************************************************************

/**
 *  Constructor for Order
 */
Order::Order(){
    this->currentPl = nullptr;
    this->game = nullptr;
};

/**
 * Parametized constructor for Order
 * @param currentPl - player issuing order
 */
 Order::Order(Player *currentPl, GameEngine *game) {
    this->currentPl = currentPl;
    this->game = game;
}

/**
 *  Default destructor for Order
 */
Order::~Order() = default;

/**
 *  Copy constructor for Order
 */
Order::Order(const Order &o){
    this->currentPl = o.currentPl;
    this->game = o.game;
}

/**
 * Assignment operator for Order
 * @param o - Orders object
 * @return Order object
 */
Order& Order::operator = (const Order& o) {
    currentPl = o.currentPl;
    game = o.game;
    return *this;
}

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

// *****************************************************************************************************************
// DEPLOY ORDER
// *****************************************************************************************************************

/**
 *  Constructor for Deploy
 */
Deploy::Deploy() : Order() {
    this->targetTer = nullptr;
    this->army_units = 0;
    this->Attach(game->getObserver());
};

Deploy::Deploy(GameEngine* game) : Order() {
    this->targetTer = nullptr;
    this->army_units = 0;
    this->Attach(game->_observers);

};

/**
 * Parametized constructor for Deploy
 * @param currentPl - player issuing order
 * @param targetTer - target territory
 * @param army_units - army units to deploy
 */
Deploy::Deploy(Territory *targetTer, Player *currentPl, int army_units, GameEngine *game) : Order(currentPl, game) {
    this->targetTer = targetTer;
    this->army_units = army_units;
    this->Attach(game->_observers);

}

/**
 * Default destructor for Deploy
 */
Deploy::~Deploy(){
    this->Detach();
}

/**
 *  Copy constructor for Deploy
 */
Deploy::Deploy(const Deploy &o) : Order(o) {
    this->targetTer = o.targetTer;
    this->army_units = o.army_units;
}

/**
 * Clone method - invokes copy constructor
 * @return Deploy - cloned order
 */
Order* Deploy::clone() const {
    return new Deploy(*this);
}

/**
 * Assignment operator for Deploy
 * @param o - deploy order
 * @return deploy order
 */
Deploy& Deploy::operator = (const Deploy& o) {

    Order::operator = (o);
    targetTer = o.targetTer;
    army_units = o.army_units;
    return *this;
}

/**
 * Stream insertion operator for Deploy
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Deploy& o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " deploys " << o.army_units << " army units to " << o.targetTer->get_name() << "." << endl;
    return out;
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Deploy::getOrderType() const {
    return orderType;
}

/**
 * Validate Deploy
 * @return boolean
 */
bool Deploy::validate() const {
    cout << *this << "Validating order." << endl;
    // return false, if the target territory doesn't belong to current player
    if (targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "Cannot deploy to territories you don't own." << endl;
        return false;
    }
    // return false, if # army units to deploy > # army units available in reinforcement pool
    else if (army_units > currentPl->getReinforcementPool()) {
        cout << "Not enough army units in your reinforcement pool." << endl;
        return false;
    }
    // return false, if the # of army units to deploy is less than 1
    else if (army_units < 1) {
        cout << "Cannot deploy less than 1 army unit." << endl;
        return false;
    }
    // return true for valid order
    else {
        cout << "Deploy order validated." << endl;
        return true;
    }
}

/**
 * Execute Deploy
 */
void Deploy::execute() {
    // if order is valid,
    if (validate()) {
        cout << "Army units in " << targetTer->get_name() << " increased from " << targetTer->get_army_units();
        // take army units from reinforcement pool
        currentPl->setReinforcementPool(currentPl->getReinforcementPool() - army_units);
        // move army units to target territory
        targetTer->set_army_units(targetTer->get_army_units() + army_units);
         cout << " to " << targetTer->get_army_units() << "." << endl;
         cout << "Deploy order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }
    Notify(this);

}

// *****************************************************************************************************************
// ADVANCE ORDER
// *****************************************************************************************************************

/**
 * Constructor for Advance
 */
Advance::Advance() : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
};

Advance::Advance(GameEngine* game) : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
    this->Attach(game->_observers);

};

/**
 * Parametized constructor for Advance
 * @param currentPl - player issuing order
 * @param sourceTer - source territory
 * @param targetTer - target territory
 * @param army_units - army units to advance
 */
Advance::Advance(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units, GameEngine *game) : Order(currentPl, game) {
    this->sourceTer = sourceTer;
    this->targetTer = targetTer;
    this->army_units = army_units;
    this->Attach(game->_observers);

}

/**
 * Default destructor for Advance
 */
Advance::~Advance(){
    this->Detach();
}

/**
 *  Copy constructor for Advance
 */
Advance::Advance(const Advance &o) : Order(o) {
    this->sourceTer = o.sourceTer;
    this->targetTer = o.targetTer;
    this->army_units = o.army_units;
}

/**
 * Clone method - invokes copy constructor
 * @return Advance - cloned order
 */
Order* Advance::clone() const {
    return new Advance(*this);
}

/**
 * Assignment operator for Advance
 * @param o - Advance order
 * @return Advance order
 */
Advance& Advance::operator = (const Advance& o) {
    Order::operator = (o);
    sourceTer = o.sourceTer;
    targetTer = o.targetTer;
    army_units = o.army_units;
    return *this;
}

/**
 * Stream insertion operator for Advance
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Advance& o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " advances " << o.army_units << " army units from " <<
    o.sourceTer->get_owner()->getName() << "'s " << o.sourceTer->get_name() << " to " <<
    o.targetTer->get_owner()->getName() << "'s " << o.targetTer->get_name() << "." << endl;
    return out;
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Advance::getOrderType() const {
    return orderType;
}

/**
 * Validate Advance
 * @return boolean
 */
bool Advance::validate() const {
    cout << *this << "Validating order." << endl;
    // return false, if the target territory belongs to a friendly player
    if (currentPl->isFriendly(targetTer->get_owner()->getPlayerID())) {
        cout << "You cannot attack this player until next turn." << endl;
        return false;
    }
    // return false, if source territory doesn't belong to current player
    else if (sourceTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "Must advance from a territory you own." << endl;
        return false;
    }
    // return false, if the source and target territory are the same
    else if (sourceTer->get_id() == targetTer->get_id()) {
        cout << "Source and target territories cannot be the same." << endl;
        return false;
    }
    // return false, if # army units to advance > # available in source territory
    else if (army_units > sourceTer->get_army_units()) {
        cout << "Not enough army units in source territory to advance." << endl;
        return false;
    }
    // return false, if the # of army units to advance is less than 1
    else if (army_units < 1) {
        cout << "Cannot advance less than 1 army unit." << endl;
        return false;
    }
    else {
        // check if the target territory is adjacent to source territory
        vector<Territory*> neighbors = sourceTer->get_neighbours();
            for (Territory *neighbor : neighbors) {
                if (neighbor->get_id() == targetTer->get_id()) {
                    // return true, target territory IS adjacent
                    cout << "Advance order validated." << endl;
                    return true;
                }
            }
        // return false, target territory IS NOT adjacent
        cout << "Cannot advance to a non-adjacent territory." << endl;
        return false;
    }
}

/**
 * Execute Advance
 */
void Advance::execute() {
    // if order is valid,
    Player* enemy = targetTer->get_owner();

    if (validate()) {
        // if both source and target territories belong to the current player (checked source territory in validate())
        if (targetTer->get_owner()->getPlayerID() == currentPl->getPlayerID()) {
            cout << "Moved " << army_units << " army units from " << currentPl->getName() << "'s " << sourceTer->get_name() << " to " << currentPl->getName() << "'s " << targetTer->get_name() << "." << endl;
            // take army units from source territory
            sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
            // move army units to target territory
            targetTer->set_army_units(targetTer->get_army_units() + army_units);
        }
        // if target territory belongs to enemy player and has 0 army units
        else if (targetTer->get_army_units() == 0) {
            // take army units from source territory
            sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
            cout << "You have conquered " << targetTer->get_name() << "!" << endl;
            cout << targetTer->get_name() << " now has " << army_units << " army units." << endl;
            cout << targetTer->get_name() << " belonged to " << targetTer->get_owner()->getName() << " and now belongs to ";
            // current player gains target territory, enemy player loses it
            // army units get added to target territory
            currentPl->conquerTerritory(targetTer);
            cout << targetTer->get_owner()->getName() << "." << endl;
            targetTer->set_army_units(army_units);



            //if enemy player is Neutral player, then the neutral player becmoes an aggressive player
            if(enemy->getStrategy() != nullptr && enemy->getStrategy()->getStrategyName() == "Neutral"){
                enemy->setStrategy(new AggressivePlayerStrategy(enemy));
            }

        }
        // if target territory belongs to enemy player and has >0 army units
        else {

            //if enemy player is Neutral player, then the neutral player becmoes an aggressive player
            if(enemy->getStrategy() != nullptr && enemy->getStrategy()->getStrategyName() == "Neutral"){
                enemy->setStrategy(new AggressivePlayerStrategy(enemy));
            }


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
                // current player gains target territory, enemy player loses it
                // surviving army units get added to target territory
                cout << "You have conquered " << targetTer->get_name() << "!" << endl;
                cout << targetTer->get_name() << " now has " << survivingAttackers << " army units." << endl;
                cout << targetTer->get_name() << " belonged to " << targetTer->get_owner()->getName() << " and now belongs to ";
                currentPl->conquerTerritory(targetTer);
                cout << targetTer->get_owner()->getName() << "." << endl;
                targetTer->set_army_units(survivingAttackers);
            }
            // if current player cannot conquer territory
            else {
                // move surviving army units back to source territory
                // reduce army units in target territory to surviving defenders
                cout << "You could not conquer " << targetTer->get_name() << "!" << endl;
                cout << survivingAttackers << " army units retreated to " << sourceTer->get_name() << "." << endl;
                cout << targetTer->get_name() << " now has " << survivingDefenders << " army units." << endl;
                sourceTer->set_army_units(sourceTer->get_army_units() + survivingAttackers);
                targetTer->set_army_units(survivingDefenders);
            }
        }
        cout << "Advance order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }
    Notify(this);

}

// *****************************************************************************************************************
// BOMB ORDER
// *****************************************************************************************************************

/**
 * Default constructor for Bomb
 */
Bomb::Bomb() : Order() {
    this->targetTer = nullptr;
};

Bomb::Bomb(GameEngine* game) : Order() {
    this->targetTer = nullptr;
    this->Attach(game->_observers);

};

/**
 * Parametized constructor for Bomb
 * @param currentPl - player issuing order
 * @param targetTer - target territory
 */
Bomb::Bomb(Territory *targetTer, Player *currentPl, GameEngine *game) : Order(currentPl, game) {
    this->targetTer = targetTer;
    this->Attach(game->_observers);

}

/**
 * Default destructor for Bomb
 */
Bomb::~Bomb() {
    this->Detach();

}

/**
 *  Copy constructor for Bomb
 */
Bomb::Bomb(const Bomb &o) : Order(o) {
    this->targetTer = o.targetTer;
}

/**
 * Clone method - invokes copy constructor
 * @return Bomb - cloned order
 */
Order* Bomb::clone() const {
    return new Bomb(*this);
}

/**
 * Assignment operator for Bomb
 * @param o - Bomb order
 * @return Bomb order
 */
Bomb& Bomb::operator = (const Bomb& o) {
    Order::operator = (o);
    targetTer = o.targetTer;
    return *this;
}

/**
 * Stream insertion operator for Bomb
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Bomb& o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " bombs " <<
        o.targetTer->get_owner()->getName() << "'s " << o.targetTer->get_name() << "." << endl;
    return out;
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Bomb::getOrderType() const {
    return orderType;
}

/**
 * Validate Bomb
 * @return boolean
 */
bool Bomb::validate() const {
    cout << *this << "Validating order." << endl;
    // return false, if the target territory belongs to a friendly player
    if (currentPl->isFriendly(targetTer->get_owner()->getPlayerID())) {
        cout << "Cannot attack this player until next turn." << endl;
        return false;
    }
    // return false, if the target territory belongs to current player
    else if (targetTer->get_owner()->getPlayerID() == currentPl->getPlayerID()) {
        cout << "Cannot bomb your own territory." << endl;
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
                    cout << "Bomb order validated." << endl;
                    return true;
                }
            }
        }
        // return false, target territory IS NOT adjacent
        cout << "Target territory must be adjacent to one of your own territories." << endl;
        return false;
    }
}

/**
 * Execute Bomb
 */
void Bomb::execute() {
    // if order is valid,
    if (validate()) {
        // halve the army units in target territory
        targetTer->set_army_units(targetTer->get_army_units() / 2);
        cout << targetTer->get_name() << " was bombed! " << targetTer->get_name() << " now has " << targetTer->get_army_units() << " army units." << endl;
        cout << "Bomb order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }

    // defining enemy player
    Player* enemy = targetTer->get_owner();

    //if enemy player is Neutral player, then the neutral player becomes an aggressive player
    if(enemy->getStrategy() != nullptr && enemy->getStrategy()->getStrategyName() == "Neutral"){
        enemy->setStrategy(new AggressivePlayerStrategy(enemy));
    }

    Notify(this);

}

// *****************************************************************************************************************
// BLOCKADE ORDER
// *****************************************************************************************************************

/**
 * Default constructor for Blockade
 */
Blockade::Blockade() : Order() {
    this->targetTer = nullptr;
    this->Detach();
}


Blockade::Blockade(GameEngine* game) : Order() {
    this->targetTer = nullptr;
    this->Attach(game->_observers);
};

/**
 * Parametized constructor for Blockade
 * @param currentPl - player issuing order
 * @param targetTer - target territory
 */
Blockade::Blockade(Territory *targetTer, Player *currentPl, GameEngine *game) : Order(currentPl, game) {
    this->targetTer = targetTer;
    this->Attach(game->_observers);

}
/**
 * Default destructor for Blockade
 */
Blockade::~Blockade() {
    this->Detach();

}

/**
 *  Copy constructor for Blockade
 */
Blockade::Blockade(const Blockade &o) : Order(o) {
    this->targetTer = o.targetTer;
}

/**
 * Clone method - invokes copy constructor
 * @return Blockade - cloned order
 */
Order* Blockade::clone() const {
    return new Blockade(*this);
}

/**
 * Assignment operator for Blockade
 * @param o - Blockade order
 * @return Blockade order
 */
Blockade& Blockade::operator = (const Blockade& o) {
    Order::operator = (o);
    targetTer = o.targetTer;
    return *this;
}

/**
 * Stream insertion operator for Blockade
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Blockade& o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " blockades " <<
        o.targetTer->get_owner()->getName() << "'s " << o.targetTer->get_name() << "." << endl;
    return out;
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Blockade::getOrderType() const {
    return orderType;
}

/**
 * Validate Blockade
 * @return boolean
 */
bool Blockade::validate() const {
    cout << *this << "Validating order." << endl;
    // return false, if target territory doesn't belong to current player
    if (targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID()) {
        cout << "Cannot blockade territories you don't own." << endl;
        return false;
    }
    // return true if order is valid
    else {
        cout << "Blockade order validated." << endl;
        return true;
    }
}

/**
 * Execute Blockade
 */
void Blockade::execute() {
    // if order is valid
    if (validate()) {
        cout << targetTer->get_name() << " has " << targetTer->get_army_units() << " army units." << endl;
        // double the army units in target territory
        targetTer->set_army_units(targetTer->get_army_units() * 2);

        // get the list of players from the game engine
        for (Player *p : game->getPlayers()) {
            // if there's already a player called Neutral, assign the target territory to them
            // remove target territory from current player and exit
            if (p->getStrategy() != nullptr && p->getStrategy()->getStrategyName() == "Neutral") {
                p->neutralConquerTerritory(targetTer);
                cout << targetTer->get_name() << " now has " << targetTer->get_army_units() << " army units and belongs to player Neutral." << endl;
                cout << "Blockade order executed." << endl;
                return;
            }
        }
        // create player called Neutral if there isn't one, add to players list
        // assign target territory to Neutral player
        // remove target territory from current player
        Player *neutral = new Player("Neutral", game);
        neutral->setStrategy(new NeutralPlayerStrategy(neutral));
        neutral->neutralConquerTerritory(targetTer);
        cout << "Player Neutral created." << endl;
        cout << targetTer->get_name() << " now has " << targetTer->get_army_units() << " army units and belongs to player Neutral." << endl;
        cout << "Blockade order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }
    Notify(this);

}

// *****************************************************************************************************************
// AIRLIFT ORDER
// *****************************************************************************************************************

/**
 * Default constructor for Airlift
 */
Airlift::Airlift() : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
};

Airlift::Airlift(GameEngine* game) : Order() {
    this->sourceTer = nullptr;
    this->targetTer = nullptr;
    this->army_units = 0;
    this->Attach(game->_observers);

};

/**
 * Parametized constructor for Airlift
 * @param currentPl - player issuing order
 * @param sourceTer - source territory
 * @param targetTer - target territory
 * @param army_units - army units to airlift
 */
Airlift::Airlift(Territory *sourceTer, Territory *targetTer, Player *currentPl, int army_units, GameEngine *game) : Order(currentPl, game) {
    this->sourceTer = sourceTer;
    this->targetTer = targetTer;
    this->army_units = army_units;
    this->Attach(game->_observers);

}

/**
 * Default destructor for Airlift
 */
Airlift::~Airlift() {
    this->Detach();

}

/**
 *  Copy constructor for Airlift
 */
Airlift::Airlift(const Airlift &o) : Order(o) {
    this->sourceTer = o.sourceTer;
    this->targetTer = o.targetTer;
    this->army_units = o.army_units;
}

/**
 * Clone method - invokes copy constructor
 * @return Airlift - cloned order
 */
Order* Airlift::clone() const {
    return new Airlift(*this);
}

/**
 * Assignment operator for Airlift
 * @param o - Airlift order
 * @return Airlift order
 */
Airlift& Airlift::operator = (const Airlift& o) {
    Order::operator = (o);
    sourceTer = o.sourceTer;
    targetTer = o.targetTer;
    army_units = o.army_units;
    return *this;
}

/**
 * Stream insertion operator for Airlift
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
ostream& operator << (ostream& out,  const Airlift& o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " airlifts " << o.army_units << " army units from " <<
        o.sourceTer->get_name() << " to " << o.targetTer->get_name() << "." << endl;
    return out;
}

/**
 * Getter for order type
 * @return constant string for type of order
 */
string Airlift::getOrderType() const {
    return orderType;
}

/**
 * Validate Airlift
 * @return boolean
 */
bool Airlift::validate() const {
    cout << *this << "Validating order." << endl;
    // return false, if either the source or target territory do not belong to current player
    if (sourceTer->get_owner()->getPlayerID() != currentPl->getPlayerID() || targetTer->get_owner()->getPlayerID() != currentPl->getPlayerID() ) {
        cout << "Can only airlift between territories you own." << endl;
        return false;
    }
    // return false, if the source and target territory are the same
    else if (sourceTer->get_id() == targetTer->get_id()) {
        cout << "Source and target territories cannot be the same." << endl;
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
        cout << "Airlift order validated." << endl;
        return true;
    }
}

/**
 * Execute Airlift
 */
void Airlift::execute() {
    // if order is valid,
    if (validate()) {
        // take army units from source territory
        sourceTer->set_army_units(sourceTer->get_army_units() - army_units);
        // move army units to target territory
        targetTer->set_army_units(targetTer->get_army_units() + army_units);
        cout << "Airlift order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }
    Notify(this);

}

// *****************************************************************************************************************
// NEGOTIATE ORDER
// *****************************************************************************************************************

/**
 * Default constructor for Negotiate
 */
Negotiate::Negotiate() : Order() {
    this->enemyPl = nullptr;
};

Negotiate::Negotiate(GameEngine* game) : Order() {
    this->enemyPl = nullptr;
    this->Attach(game->_observers);

};

/**
 * Parametized constructor for Negotiate
 * @param currentPl - player issuing order
 * @param enemyPl - enemy player to negotiate with
 */
Negotiate::Negotiate(Player *currentPl, Player *enemyPl, GameEngine *game) : Order(currentPl, game) {
    this->enemyPl = enemyPl;
    this->Attach(game->_observers);
}

/**
 * Default destructor for Negotiate
 */
    Negotiate::~Negotiate(){
    this->Detach();

}

/**
 *  Copy constructor for Negotiate
 */
    Negotiate::Negotiate(
    const Negotiate &o){
        this->enemyPl = o.enemyPl;
    }
/**
 * Clone method - invokes copy constructor
 * @return Negotiate - cloned order
 */
    Order *Negotiate::clone() const {
        return new Negotiate(*this);
    }

/**
 * Assignment operator for Negotiate
 * @param o - Negotiate order
 * @return Negotiate order
 */
    Negotiate &Negotiate::operator=(const Negotiate &o) {
        Order::operator=(o);
        enemyPl = o.enemyPl;
        return *this;
    }

/**
 * Stream insertion operator for Negotiate
 * @param o - Orders object
 * @param out - ostream object
 * @return ostream object
 */
    ostream &operator<<(ostream &out, const Negotiate &o) {
    out << o.getOrderType() << ": " << o.currentPl->getName() << " negotiates with " <<
        o.enemyPl->getName() << "." << endl;
    return out;
    }

/**
 * Getter for order type
 * @return constant string for type of order
 */
    string Negotiate::getOrderType() const {
        return orderType;
    }

/**
 * Validate Negotiate
 * @return boolean
 */
bool Negotiate::validate() const {
    cout << *this << "Validating order." << endl;
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
        cout << "Negotiate order validated." << endl;
        return true;
    }
}

/**
 * Execute Negotiate
 */
void Negotiate::execute() {
    // if order is valid,
    if (validate()) {
        // add each player to the other player's friendly list
        currentPl->addFriendly(enemyPl->getPlayerID());
        enemyPl->addFriendly(currentPl->getPlayerID());
        cout << "Player " << currentPl->getName() << " negotiated with Player " << enemyPl->getName() << ". Both players cannot attack each other this turn." << endl;
        cout << "Negotiate order executed." << endl;
    }
    // if order is invalid, display message
    else {
        cout << "Invalid order. Order will not be executed." << endl;
    }
    Notify(this);

}

// *****************************************************************************************************************
// ORDERSLIST
// *****************************************************************************************************************

/**
 * Constructor for OrdersList
 */
OrdersList::OrdersList() = default;

OrdersList::OrdersList(GameEngine* game)
{
    this->Attach(game->_observers);
}
/**
 * Destructor for OrdersList
 */
OrdersList::~OrdersList()
{
    int size = _ordersList.size();

    for (int i = 0; i < size; i++) {
        delete _ordersList[i];
    }
    _ordersList.clear();
    this->Detach();
};

/**
 * Copy constructor for OrdersList - makes deep copy
 * @param ol - OrdersList object
 */
OrdersList::OrdersList(const OrdersList &ol) {
    int size = ol._ordersList.size();

    _ordersList = vector<Order *>(size);
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
ostream &operator<<(ostream &out, const OrdersList &ol) {
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
OrdersList &OrdersList::operator=(const OrdersList &ol) {
    // check self-assignment
    if (this == &ol)
        return *this;

    // free memory of original orders list
    for (int i = 0; i < _ordersList.size(); i++) {
        delete _ordersList[i];
    }

    int size = ol._ordersList.size();
    // set list size equal to target orders list
    _ordersList = vector<Order *>(size);
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
void OrdersList::add(Order *o) {
    // add new order to vector
    _ordersList.push_back(o);
    Notify(this);

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
        delete _ordersList[pos - 1];
        // resize vector
        _ordersList.erase(_ordersList.begin() + pos - 1);
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
            Order *temp = _ordersList[currentPos - 1];
            // move the order at target position to current position
            _ordersList[currentPos - 1] = _ordersList[newPos - 1];
            // move the order at current position to target position
            _ordersList[newPos - 1] = temp;
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

/**
 * Method to execute a single order
 */
    void OrdersList::executeOrder() {
        int size = _ordersList.size();

        _ordersList.front()->execute();
        delete _ordersList.front();
        _ordersList.erase(_ordersList.begin());
        cout << "New size of orderlist : " << size << " -> " << _ordersList.size() << endl;
    }


/**
 * Method to get top order
 */
 Order *OrdersList::getTopOrder() {
        cout << "Top order : ";
        Order *o = _ordersList.front();
        cout << *o << endl;
        return o;
 }

/**
 * Getter for order vector
 */
 vector<Order *> OrdersList::getOrderList() {
    return _ordersList;
}

/**
 * StringToLog method for order
 */
string Order::stringToLog() {
        return "Order executed: " + getOrderType();
}

/**
 * StringToLog method for OrdersList
 */
string OrdersList::stringToLog() {
    string lastOrder = _ordersList.back()->getOrderType();
    return "Order added: " + lastOrder;
}

