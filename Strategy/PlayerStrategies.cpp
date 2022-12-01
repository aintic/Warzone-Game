#include <vector>
#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include "Player.h"

#include "algorithm" //not sure if i need this

class Territory;

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

PlayerStrategy::PlayerStrategy(Player *p) {
    player = p;
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

    Hand* playerHand = player->getHand();
    vector<Card *> playerCards = playerHand->getCards();
    GameEngine* game = player->getGame();
    Deck* deck = game->getDeck();
    vector<Territory *> playerTerritories = player->getTerritories();
    Territory* weakestT = player->toDefend().front();
    Territory* strongestT = player->toDefend().back();

    if (player->getIssuableReinforcementPool() != 0) {
        vector<Territory *> toDefendTerritories = this->toDefend();
        int armiesToDeploy = player->getIssuableReinforcementPool();
        if (toDefendTerritories.size() != 1) {
            int armyUnitDifference = (strongestT->get_army_units() + strongestT->get_issued_army_units()) -
                    (weakestT->get_army_units() + weakestT->get_issued_army_units());
            if(player->getIssuableReinforcementPool() - armyUnitDifference > 0){
                armiesToDeploy = player->getIssuableReinforcementPool() - armyUnitDifference; // only deploys the necessary amount
            }else{
                armiesToDeploy = player->getIssuableReinforcementPool(); // deploys all issuable armies
            }
        }
        player->getPlayerOrderList()->add(
                new Deploy(weakestT, player, armiesToDeploy, player->getGame())); // deploy armies to the weakest territory
        player->setIssuableReinforcementPool(player->getIssuableReinforcementPool() - armiesToDeploy); // decrement player's reinforcement pool
        weakestT->set_issued_army_units(weakestT->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units
        cout << *player << " issued a new deploy order of " << armiesToDeploy << " armies to "
             << weakestT->get_name() << endl;
    }else if(!playerCards.empty() && !onlyNonPlayableCards(player)){
        for(int i = 0; i < playerCards.size(); i++){
            playerHand->play(*deck, player, i);
            break;
//            player->getHand()->play(*player->getGame()->getDeck(), player, 0);
//            if(playerCards.at(i)->getCardType() != "Bomb" && playerCards.at(i)->getCardType() != "Blockade"){
//                playerHand->play(*deck, player, i);
//                break;
//            }
        }
    }else if (player->getAdvanceDefendOrdersIssued() < 1 && toDefend().size() > 1) { // issue at most 1 advance defend order
        // send half source territory army units
        player->getPlayerOrderList()->add(new Advance(strongestT, weakestT, player,
                                    (strongestT->get_army_units() + strongestT->get_issued_army_units()) / 2, game));
        player->setAdvanceDefendOrdersIssued(player->getAdvanceDefendOrdersIssued() + 1); // increment orders issued
        cout << *player << " issued a new advance order from " << strongestT->get_name() << " to their own territory "
             << weakestT->get_name() << endl;
    } else {
        cout << *player << " is done issuing orders" << endl;
        return player->setIsDoneIssuingOrders(true);
    }
}

//Only used to issue Negotiate orders. Player will prioritize the winning player to Negotiate with.
vector<Territory *> BenevolentPlayerStrategy::toAttack() {
    vector<Territory *> toAttackTerritories;
    for (Territory *ownedTerritory: player->getTerritories()) { //for each owned territory
        for (Territory *neighborTerritory: ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner() != player) {  //if the current player does not own the neighbor territory
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
    sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs) {
        return lhs->get_army_units() < rhs->get_army_units();
    });
    return toAttackTerritories;
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
    auto territories = player->getTerritories();
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territories;
}

string BenevolentPlayerStrategy::getStrategyName() const {
    return strategyName;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p) {
}

bool BenevolentPlayerStrategy::onlyNonPlayableCards(Player *p) {
    Hand* playerHand = player->getHand();
    vector<Card *> playerCards = playerHand->getCards();
    bool onlyNonPlayable = true;
    for(int i = 0; i < playerCards.size(); i++){
        if(playerCards.at(i)->getCardType() != "Bomb" && playerCards.at(i)->getCardType() != "Blockade"){
            onlyNonPlayable = false;
        }
    }
    return onlyNonPlayable;
}