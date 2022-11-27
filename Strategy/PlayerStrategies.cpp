#include "PlayerStrategies.h"

//Neutral Player
//defualt constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
    this->player = player;
}
void NeutralPlayerStrategy::issueOrder() {

}

vector<Territory *> NeutralPlayerStrategy::toAttach() {

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

vector<Territory *> CheaterPlayerStrategy::toAttach() {
    return vector<Territory *>();
}

vector<Territory *> CheaterPlayerStrategy::toDefend() {
    return vector<Territory *>();
}


//Human Player
void HumanPlayerStrategy::issueOrder() {

}

vector<Territory *> HumanPlayerStrategy::toAttach() {
    return vector<Territory *>();
}

vector<Territory *> HumanPlayerStrategy::toDefend() {
    return vector<Territory *>();
}


//Aggressive Player
void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory *> AggressivePlayerStrategy::toAttach() {
    return vector<Territory *>();
}

vector<Territory *> AggressivePlayerStrategy::toDefend() {
    return vector<Territory *>();
}


//Benevolent Player
void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory *> BenevolentPlayerStrategy::toAttach() {
    return vector<Territory *>();
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
    return vector<Territory *>();
}
