#include "PlayerStrategies.h"


// Constant strategy names for subclasses
const string NeutralPlayerStrategy::strategyName = "Neutral";
const string CheaterPlayerStrategy::strategyName = "Cheater";
const string HumanPlayerStrategy::strategyName = "Human";
const string AggressivePlayerStrategy::strategyName = "Aggressive";
const string BenevolentPlayerStrategy::strategyName = "Benevolent";


//Player Strategy base class
PlayerStrategy::PlayerStrategy() {
    /* TO-DO */
}

PlayerStrategy::PlayerStrategy(const Player &p) {
    /* TO-DO */
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &) {
    /* TO-DO */
    return *this;
}

Player *PlayerStrategy::getPlayer() {
    return player;
}

void PlayerStrategy::setPlayer(Player* p) {
    this->player = p;
}

//Neutral Player
//default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
    this->player = player;
    player->setStrategy(this);

}
// Copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &neutralPlayerStrategy) {
    this->player = neutralPlayerStrategy.player;
    this->player->setStrategy(this);
}

// Assignment operator
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &neutralPlayerStrategy) {
    this->player = neutralPlayerStrategy.player;
    this->player->setStrategy(this);
    return *this;
}


void NeutralPlayerStrategy::issueOrder() {
    player->setIsDoneIssuingOrders(true);

}

vector<Territory *> NeutralPlayerStrategy::toAttack() {
    //return empty territories
    vector<Territory*> territories;
    return territories;
}

vector<Territory *> NeutralPlayerStrategy::toDefend() {
    vector<Territory *> territories = player->getTerritories();

    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return  (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
}

string NeutralPlayerStrategy::getStrategyName() const {
    return strategyName;
}


//Cheater Player
void CheaterPlayerStrategy::issueOrder() {

}

vector<Territory *> CheaterPlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> CheaterPlayerStrategy::toDefend() {
    return vector<Territory *>();
}

string CheaterPlayerStrategy::getStrategyName() const {
    return strategyName;
}


//Human Player
void HumanPlayerStrategy::issueOrder() {

}

vector<Territory *> HumanPlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> HumanPlayerStrategy::toDefend() {
    return vector<Territory *>();
}

string HumanPlayerStrategy::getStrategyName() const {
    return strategyName;
}


//Aggressive Player
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) {
    this->player = player;
    player->setStrategy(this);
}

void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory *> AggressivePlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> AggressivePlayerStrategy::toDefend() {
    return vector<Territory *>();
}

string AggressivePlayerStrategy::getStrategyName() const {
    return strategyName;
}



//Benevolent Player
void BenevolentPlayerStrategy::issueOrder() {
}

vector<Territory *> BenevolentPlayerStrategy::toAttack() {
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
}

string BenevolentPlayerStrategy::getStrategyName() const {
    return strategyName;
}