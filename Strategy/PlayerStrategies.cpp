#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "Player.h"


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
    return;
}

// returns neighbouring enemy territories from weakest to strongest
vector<Territory *> AggressivePlayerStrategy::toAttack() {
    vector<Territory*> territories = player->getTerritories();
    vector<Territory*> toAttackTerritories;
    for (Territory *ownedTerritory : territories){ //for each owned territory
        for (Territory *neighborTerritory : ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner()->getPlayerID() != player->getPlayerID()) {  //if the current player does not own the neighbor territory
                // check if territory is already in toAttackTerritories
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) { //if territory is not already in toAttackTerritories add it
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    // sort toAttack territories by # of army units ascending
    sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs){
        return  lhs->get_army_units() < rhs->get_army_units();
    });
    return toAttackTerritories;
}

// returns own territories from weakest to strongest
vector<Territory *> AggressivePlayerStrategy::toDefend() {
    vector<Territory *> territories = player->getTerritories();
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs) {
        return (lhs->get_army_units() + lhs->get_issued_army_units()) <
               (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territories;
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