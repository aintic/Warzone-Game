#include "PlayerStrategies.h"

//Neutral Player
//default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
    this->player = player;
}
void NeutralPlayerStrategy::issueOrder() {

}

vector<Territory *> NeutralPlayerStrategy::toAttack() {

    return vector<Territory *>();
}

vector<Territory *> NeutralPlayerStrategy::toDefend() {
    vector<Territory *> territories = player->getTerritories();

    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return  (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
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


//Human Player
void HumanPlayerStrategy::issueOrder() {

}

vector<Territory *> HumanPlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> HumanPlayerStrategy::toDefend() {
    return vector<Territory *>();
}


//Aggressive Player
void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory *> AggressivePlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> AggressivePlayerStrategy::toDefend() {
    return vector<Territory *>();
}


//Benevolent Player
void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory *> BenevolentPlayerStrategy::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
    return vector<Territory *>();
}
