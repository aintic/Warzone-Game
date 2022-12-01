#include "Player.h"
#include "../GameEngine/GameEngine.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../Strategy/PlayerStrategies.h"
#include "algorithm"
using std::find_if;
#include <vector>
#include <random>
using std::random_device;
using std::uniform_int_distribution;

int Player::uniqueID = 0;

//Default constructor
Player::Player() {
    this->playerID = ++uniqueID;
    this->name = "player";
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand;
    this->order_list = new OrdersList();
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
    this->game = nullptr;
}

//Constructor with name only
Player::Player(string name, GameEngine* game) {
    this->playerID = ++uniqueID;
    this->name = name;
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand();
    this->order_list = new OrdersList();
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
    this->game = game;
}


//Constructor with player id, territories, hand and orders
//So, the player owns territories, owns hand cards, list of orders and list of friendly players negotiated with
Player::Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders, GameEngine *game) {
    this->playerID = ++uniqueID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
    this->game = game;
}

//copy constructor
Player::Player(const Player& p){
    playerID = getPlayerID();
    name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
    this->friendlyList = p.friendlyList;
    this->conquerer = p.conquerer;
    this->game = p.game;
}

//destructor
Player::~Player()
{
    for (int i = 0; i < game->players.size(); i++){
        if(game->players.at(i) == this) {
            game->players.erase(game->players.begin() + i);
            break;
        }
    }
    delete hand;
    delete order_list;
    territories.clear();
    friendlyList.clear();
}

//assignment operator
Player& Player::operator=(const Player& p){
    playerID = p.playerID;
    name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
    this->friendlyList = p.friendlyList;
    this->conquerer = p.conquerer;
    this->game = p.game;
    return *this;
}

//returns a list of territories to be defended
vector<Territory*> Player:: toDefend(){
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return  (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return this->territories;
}

//returns a list of territories to be attacked
vector<Territory*> Player:: toAttack(){
    vector<Territory*> toAttackTerritories;
    for (Territory *ownedTerritory : territories){ //for each owned territory
        for (Territory *neighborTerritory : ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner() != this) {  //if the current player does not own the neighbor territory
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

//returns the strongest owned neighbor
Territory* Player::strongestOwnedNeighbor(Territory* territory) {
    vector<Territory*> ownedNeighbors;
    for (Territory *terr : territories) {
        for (Territory *neighborTerr : terr->get_neighbours()){
            if (neighborTerr == territory){
                ownedNeighbors.push_back(terr);
            }
        }
    }
    return *max_element(ownedNeighbors.begin(), ownedNeighbors.end(), [](Territory* a, Territory* b){
        return a->get_army_units() < b->get_army_units();
    });
}

void Player::addOrder(Order *o){
    this->order_list->add(o);
}

//creates an order object and adds it to the list of orders
void Player::issueOrder() {
    if(issuableReinforcementPool != 0) {
        vector<Territory*> toDefendTerritories = this->toDefend();
        int armiesToDeploy = issuableReinforcementPool;
        if (toDefendTerritories.size() != 1) {
            random_device rd;
            uniform_int_distribution<int> dist(1, issuableReinforcementPool);
            armiesToDeploy = dist(rd);
        }

        Territory *targetTerr = this->toDefend().front(); // owned territory with the lowest number of army units (actual + issued)
        order_list->add(new Deploy(targetTerr, this, armiesToDeploy, game)); // deploy armies to the weakest territory
        issuableReinforcementPool -= armiesToDeploy; // decrement player's reinforcement pool
        targetTerr->set_issued_army_units(targetTerr->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units

        cout << *this << " issued a new deploy order of " << armiesToDeploy << " armies to " << targetTerr->get_name() << endl;
    }
    else if (!this->hand->getCards().empty()) {
        hand->play(*game->getDeck(), this, 0); // play every card in player's hand
    }
    else if (advanceAttackOrdersIssued < 2 && advanceAttackOrdersIssued < toAttack().size()){ // issue at most 2 advance attack orders
        Territory *targetTerr = toAttack().at(advanceAttackOrdersIssued);
        Territory *sourceTerr = strongestOwnedNeighbor(targetTerr);
        // send all source territory army units except 1
        order_list->add(new Advance(sourceTerr, targetTerr, this, sourceTerr->get_army_units() + sourceTerr->get_issued_army_units(), game));

        advanceAttackOrdersIssued++; // increment orders issued
        cout << *this << " issued a new advance order from " << sourceTerr->get_name() << " to an enemy territory " << targetTerr->get_name() << endl;
    }
    else if (advanceDefendOrdersIssued < 1 && toDefend().size() > 1){ // issue at most 1 advance defend order
        Territory *targetTerr = toDefend().front(); // weakest owned territory
        Territory *sourceTerr = toDefend().back(); // strongest owned territory
        // send half source territory army units
        order_list->add(new Advance(sourceTerr, targetTerr, this, (sourceTerr->get_army_units() + sourceTerr->get_issued_army_units()) / 2 , game));

        advanceDefendOrdersIssued++; // increment orders issued
        cout << *this << " issued a new advance order from " <<  sourceTerr->get_name() << " to their own territory " << targetTerr->get_name() << endl;
    }
    else {
        cout << *this << " is done issuing orders" << endl;
        this->isDoneIssuingOrders = true;
    }
}

//adds a territory to the list of owned territories
void Player::addTerritory(Territory* t){
    territories.push_back(t); // can be used like p1->addTerritory(t1*)
    t->set_owner(this);
}

//removes territory from players list of territories
void Player::removeTerritory(Territory* t) {
    territories.erase(remove(territories.begin(), territories.end(), t), territories.end());
}

//makes the territory exchange between 2 players, when territory gets conquered
void Player::conquerTerritory(Territory* t) {
    Player* loser = t->get_owner();
    loser->removeTerritory(t);
    this->addTerritory(t);
    this->conquerer = true;
}

void Player::neutralConquerTerritory(Territory* t) {
    Player* loser = t->get_owner();
    loser->removeTerritory(t);
    this->addTerritory(t);
}

// add a friendly player when executing Negotiate order
void Player::addFriendly(int playerID) {
    friendlyList.push_back(playerID);
}

// reset player's friendly list (at the end of every turn)
void Player::resetFriendlyList() {
    friendlyList.clear();
}

// check if a player is friendly to current player
bool Player::isFriendly(int playerID) {
    int size = friendlyList.size();

    for (int i = 0; i < size; i++) {
        if (friendlyList[i] == playerID) {
            return true;
        }
    }

    return false;
}

void Player::resetConquerer() {
    this->conquerer = false;
}

//getters
int Player::getPlayerID(){
    return this->playerID;
}

string Player:: getName(){
    return name;
}

GameEngine* Player::getGame() {
    return game;
}

Hand* Player::getHand(){
    return hand;
}
OrdersList* Player :: getPlayerOrderList(){
    return order_list;
}

vector<Territory*> Player::getTerritories(){
    return territories;
}

int Player::getNumTerritories() {
    return this->getTerritories().size();
}

int Player::getReinforcementPool() {
    return reinforcementPool;
}

bool Player::getConquerer() {
    return conquerer;
}

//setters

void Player::setGame(GameEngine* game) {
    this->game = game;
}

void Player::setPlayerOrderList(OrdersList* orders){
    this->order_list = orders;
}

void Player::setTerritories(vector<Territory*> t){
    this->territories = t;
}

void Player::setReinforcementPool(int armies) {
    this->reinforcementPool = armies;
}

void Player::setIssuableReinforcementPool(int armies) {
    this->issuableReinforcementPool = armies;
}

void Player::setAdvanceAttackOrdersIssued(int numArmies){
    this->advanceAttackOrdersIssued = numArmies;
}

void Player::setAdvanceDefendOrdersIssued(int numArmies){
    this->advanceDefendOrdersIssued = numArmies;
}

void Player::setIsDoneIssuingOrders(bool b){
    this->isDoneIssuingOrders = b;
}

bool Player::getIsDoneIssuingOrders() {
    return this->isDoneIssuingOrders;
};

ostream& operator<<(ostream& os, Player& p){
    return os << "Name: " << p.getName() << ", ID: " << p.getPlayerID();
}
//setter for strategy
void Player::setStrategy(PlayerStrategy* newStrategy) {
    if(newStrategy != nullptr) {
        delete this->strategy;
    }
    this->strategy = newStrategy;
}

int Player::getIssuableReinforcementPool() const {
    return issuableReinforcementPool;
}

//getter for strategy
PlayerStrategy* Player::getStrategy() {
    return this->strategy;
}

int Player::getAdvanceDefendOrdersIssued() const {
    return advanceDefendOrdersIssued;
}

const vector<int> &Player::getFriendlyList() const {
    return friendlyList;
}

int Player::getAdvanceAttackOrdersIssued() const {
    return advanceAttackOrdersIssued;
}