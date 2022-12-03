#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include "Player.h"
#include <vector>
#include <algorithm>

class Territory;

// Constant strategy names for subclasses
const string NeutralPlayerStrategy::strategyName = "Neutral";
const string CheaterPlayerStrategy::strategyName = "Cheater";
const string HumanPlayerStrategy::strategyName = "Human";
const string AggressivePlayerStrategy::strategyName = "Aggressive";
const string BenevolentPlayerStrategy::strategyName = "Benevolent";


// *****************************************************************************************************************
// PLAYER STRATEGY (ABSTRACT BASE CLASS)
// *****************************************************************************************************************

// default constructor
PlayerStrategy::PlayerStrategy() {
    this->player = nullptr;
};

// parametized constructor
PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
    player->setStrategy(this);
}

// copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps) {
    this->player = ps.player;
    player->setStrategy(this);
}

// assignment operator
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &ps) {
    if (&ps != this) {
        this->player = ps.player;
        player->setStrategy(this);
    }
    return *this;
}

// stream insertion operator
ostream& operator << (ostream& out,  const PlayerStrategy& ps) {
    cout <<  ps.getStrategyName();
    return out;
}

// player getter
Player *PlayerStrategy::getPlayer() {
    return player;
}

// player setter
void PlayerStrategy::setPlayer(Player* p) {
    this->player = p;
}

// *****************************************************************************************************************
// NEUTRAL PLAYER STRATEGY
// *****************************************************************************************************************

//default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategy() {}

// parametized constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}

// Copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &neutralPlayerStrategy) : PlayerStrategy(neutralPlayerStrategy){}

// Assignment operator
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &neutralPlayerStrategy) {
    PlayerStrategy::operator = (neutralPlayerStrategy);
    return *this;
}

// clone method
NeutralPlayerStrategy* NeutralPlayerStrategy::clone() const {
    return new NeutralPlayerStrategy(*this);
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
    return territories;
}

string NeutralPlayerStrategy::getStrategyName() const {
    return strategyName;
}

// *****************************************************************************************************************
// CHEATER PLAYER STRATEGY
// *****************************************************************************************************************

// clone method
CheaterPlayerStrategy* CheaterPlayerStrategy::clone() const {
    return new CheaterPlayerStrategy(*this);
}

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

// *****************************************************************************************************************
// HUMAN PLAYER STRATEGY
// *****************************************************************************************************************

// clone method
HumanPlayerStrategy* HumanPlayerStrategy::clone() const {
    return new HumanPlayerStrategy(*this);
}

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

// *****************************************************************************************************************
// AGGRESSIVE PLAYER STRATEGY
// *****************************************************************************************************************

// default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategy() {
    this->airliftCardIssued = 0;
}

// parametized constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {
    this->airliftCardIssued = 0;
}

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &aps) : PlayerStrategy(aps) {
    this->airliftCardIssued = aps.getAirliftCardIssued();
};

// assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &aps) {
    PlayerStrategy::operator = (aps);
    this->airliftCardIssued = aps.getAirliftCardIssued();
    return *this;
}

// clone method
AggressivePlayerStrategy* AggressivePlayerStrategy::clone() const {
    return new AggressivePlayerStrategy(*this);
}

// stream insertion operator
ostream& operator << (ostream& out,  const AggressivePlayerStrategy& aps) {
    cout << aps.getStrategyName();
    return out;
}

// issue order method - either issue 1 deploy order, 1 card order, 1 advance defend, 1 advance attack or no order
void AggressivePlayerStrategy::issueOrder() {
    int issuableReinforcementPool = player->getIssuableReinforcementPool();
    int advanceAttackOrdersIssued = player->getAdvanceAttackOrdersIssued();
    int advanceDefendOrdersIssued = player->getAdvanceDefendOrdersIssued();
    int defendListSize = toDefend().size();
    int attackListSize = toAttack().size();

    // issue deploy order
    if(issuableReinforcementPool != 0) {
        int armiesToDeploy = issuableReinforcementPool;
        Territory *targetTerr;
        // in 1st turn, deploy to territory most surrounded by enemies
        if (player->getGame()->turn == 1) {
            targetTerr = terrMostSurroundedByEnemies();
        }
        // in other turns, deploy to territory with highest armies (actual + issued)
        else {
            targetTerr = this->toDefend().back();
        }
        player->getPlayerOrderList()->add(new Deploy(targetTerr, player, armiesToDeploy, player->getGame())); // deploy entire reinforcement pool to the target territory
        player->setIssuableReinforcementPool(player->getIssuableReinforcementPool()-armiesToDeploy); // decrement player's reinforcement pool
        targetTerr->set_issued_army_units(targetTerr->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units
        cout << *player << " issued a new deploy order of " << armiesToDeploy << " armies to " << targetTerr->get_name() << endl;
    }
    // or issue card order
    else if (!player->getHand()->getCards().empty()) {
        // issue any card orders
        player->getHand()->play(*player->getGame()->getDeck(), player, 0);
    }
    // or issue advance defend order - move armies from own territories
    else if (advanceDefendOrdersIssued < 1 && defendListSize > 1){
        // if player owns >2 territories, move armies from 2nd strongest territory to strongest territory
        // if player owns <2 territories, move armies from one to the other
        vector<Territory*> ownedTers = toDefend();
        Territory *targetTerr = ownedTers.back();
        Territory *sourceTerr = ownedTers.front();
        if (defendListSize > 2) {
            sourceTerr = ownedTers.at(defendListSize - 2);
        }
        player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player, (sourceTerr->get_army_units() + sourceTerr->get_issued_army_units()) , player->getGame()));
        player->setAdvanceDefendOrdersIssued(++advanceDefendOrdersIssued); // increment orders issued
        cout << *player << " issued a new advance order from " <<  sourceTerr->get_name() << " to their own territory " << targetTerr->get_name() << endl;
    }
    // or issue advance attack order - move armies to strongest terr to enemy terr
    else if (player->getAdvanceAttackOrdersIssued() < 1 && advanceAttackOrdersIssued < attackListSize){ // issue at most 1 advance attack orders
        // move armies from the strongest terr
        Territory *sourceTerr = toDefend().back();
        Territory *targetTerr = toAttack().front();
        int index = 0;
        bool found = false;
        // go down attack list to find weakest *neighbouring* enemy territory
        // if attack list is exhausted and no neighbouring enemy territory found, don't issue order
        while (index < attackListSize && !found) {
            if (targetIsAdjacent(sourceTerr, targetTerr)) {
                found = true;
            }
            else if ((index+1) < attackListSize){
                index++;
                targetTerr = toAttack().at(index);
            }
            else {
                break;
            }
        }
        if (found) {
            player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player, sourceTerr->get_army_units() + sourceTerr->get_issued_army_units(), player->getGame()));
            player->setAdvanceAttackOrdersIssued(++advanceAttackOrdersIssued); // increment orders issued
            cout << *player << " issued a new advance order from " << sourceTerr->get_name() << " to an enemy territory " << targetTerr->get_name() << endl;
        }
        else {
            player->setAdvanceAttackOrdersIssued(++advanceAttackOrdersIssued); // increment orders issued
            cout << *player << " cannot issue more advance order this turn. No neighbouring enemy territory found." << endl;
        }

    }
    // no more order to issue
    else {
        cout << *player << " is done issuing orders" << endl;
        setAirliftCardIssued(0);
        player->setIsDoneIssuingOrders(true);
    }
}

// returns enemy territories from weakest to strongest
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

// find the territory most surrounded by enemy territories
Territory* AggressivePlayerStrategy::terrMostSurroundedByEnemies() const {
    vector<Territory*> territories = player->getTerritories();
    std::map<Territory*, int> enemyCount;
    for (Territory *t : territories) {
        vector<Territory*> neighbors = t->get_neighbours();
        for (Territory *neighbor : neighbors) {
            if (neighbor->get_owner()->getPlayerID() != player->getPlayerID()) {
                // enemy territory found, increment enemy count
                enemyCount[t]++;
            }
        }
    }
    std::map<Territory*, int>::iterator mostEnemy
            = std::max_element(enemyCount.begin(),enemyCount.end(),[] (const std::pair<Territory*, int>& a, const std::pair<Territory*, int>& b)->bool{ return a.second < b.second; } );
    return mostEnemy->first;
}

// check if target territory is adjacent to source territory
bool AggressivePlayerStrategy::targetIsAdjacent(Territory *source, Territory *target) const {
        vector<Territory*> neighbors = source->get_neighbours();
        for (Territory *neighbor : neighbors) {
            if (neighbor->get_id() == target->get_id()) {
                // return true, target territory IS adjacent
                return true;
            }
        }
        return false;
}

// strategy name getter
string AggressivePlayerStrategy::getStrategyName() const {
    return strategyName;
}

// airliftCardIssued getter
int AggressivePlayerStrategy::getAirliftCardIssued() const {
    return airliftCardIssued;
}

// airliftCardIssued setter
void AggressivePlayerStrategy::setAirliftCardIssued(int airliftCardIssued) {
    this->airliftCardIssued = airliftCardIssued;
}

// *****************************************************************************************************************
// BENEVOLENT PLAYER STRATEGY
// *****************************************************************************************************************

BenevolentPlayerStrategy* BenevolentPlayerStrategy::clone() const {
    return new BenevolentPlayerStrategy(*this);
}

void BenevolentPlayerStrategy::issueOrder() {
}

vector<Territory *> BenevolentPlayerStrategy::toAttack() {
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
}

string BenevolentPlayerStrategy::getStrategyName() const {
    return strategyName;
}

