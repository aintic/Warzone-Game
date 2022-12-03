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

// *****************************************************************************************************************
// CONSTRUCTORS, DESTRUCTOR, OPERATORS
// *****************************************************************************************************************

//Default constructor
Player::Player() {
    this->playerID = ++uniqueID;
    this->game = nullptr;
    this->name = "player";
    this->hand = new Hand;
    vector<Territory*> t;
    this->territories = t;
    this->order_list = new OrdersList();
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    this->isDoneIssuingOrders = false;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
}

// Parametized constructor with player name, territories, hand, orders and game engine
Player::Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders, GameEngine *game) {
    this->playerID = ++uniqueID;
    this->game = game;
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    this->order_list = orders;
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    this->isDoneIssuingOrders = false;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
}

// Parametized constructor with name only
Player::Player(string name, GameEngine* game) {
    this->playerID = ++uniqueID;
    this->game = game;
    this->name = name;
    this->hand = new Hand();
    vector<Territory*> t;
    this->territories = t;
    this->order_list = new OrdersList();
    this->reinforcementPool = 0;
    this->issuableReinforcementPool = 0;
    this->advanceAttackOrdersIssued = 0;
    this->advanceDefendOrdersIssued = 0;
    this->isDoneIssuingOrders = false;
    vector<int> f;
    this->friendlyList = f;
    this->conquerer = false;
}

//copy constructor
Player::Player(const Player& p){
    this->playerID = ++uniqueID;
    this->strategy = p.getStrategy()->clone();
    this->game = p.getGame();
    this->name = p.getName();
    this->hand = new Hand(*(p.getHand()));
    this->territories = p.getTerritories();
    this->order_list = new OrdersList(*(p.getPlayerOrderList()));
    this->reinforcementPool = p.getReinforcementPool();
    this->issuableReinforcementPool = p.getIssuableReinforcementPool();
    this->advanceAttackOrdersIssued = p.getAdvanceAttackOrdersIssued();
    this->advanceDefendOrdersIssued = p.getAdvanceDefendOrdersIssued();
    this->isDoneIssuingOrders = p.getIsDoneIssuingOrders();
    this->friendlyList = p.getFriendlyList();
    this->conquerer = p.conquerer;
}

//assignment operator
Player& Player::operator=(const Player& p){
    if (&p != this) {
        delete this->hand;
        delete this->order_list;
        delete this->strategy;
        this->strategy = p.getStrategy()->clone();
        this->game = p.getGame();
        name = p.getName();
        this->hand = new Hand(*(p.getHand()));
        this->territories = p.getTerritories();
        this->order_list = new OrdersList(*(p.getPlayerOrderList()));
        this->reinforcementPool = p.getReinforcementPool();
        this->issuableReinforcementPool = p.getIssuableReinforcementPool();
        this->advanceAttackOrdersIssued = p.getAdvanceAttackOrdersIssued();
        this->advanceDefendOrdersIssued = p.getAdvanceDefendOrdersIssued();
        this->isDoneIssuingOrders = p.getIsDoneIssuingOrders();
        this->friendlyList = p.getFriendlyList();
        this->conquerer = p.conquerer;
    }
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, Player& p){
    return os << "Name: " << p.getName() << ", ID: " << p.getPlayerID();
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
    delete strategy;
    delete hand;
    delete order_list;
    territories.clear();
    friendlyList.clear();
}

// *****************************************************************************************************************
// METHODS
// *****************************************************************************************************************

//returns a list of territories to be defended
vector<Territory*> Player:: toDefend(){
    if(strategy == nullptr) {
        sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs) {
            return (lhs->get_army_units() + lhs->get_issued_army_units()) <
                   (rhs->get_army_units() + rhs->get_issued_army_units());
        });
        return this->territories;
    }
    else {
        return this->strategy->toDefend();
    }
}

//returns a list of territories to be attacked
vector<Territory*> Player:: toAttack(){
    if(strategy == nullptr) {
        vector<Territory *> toAttackTerritories;
        for (Territory *ownedTerritory: territories) { //for each owned territory
            for (Territory *neighborTerritory: ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
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
        sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs) {
            return lhs->get_army_units() < rhs->get_army_units();
        });
        return toAttackTerritories;
    }
    else {
        return strategy->toAttack();
    }
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

//creates an order object and adds it to the list of orders
void Player::issueOrder() {
    if(strategy == nullptr) {
        if (issuableReinforcementPool != 0) {
            vector<Territory *> toDefendTerritories = this->toDefend();
            int armiesToDeploy = issuableReinforcementPool;
            if (toDefendTerritories.size() != 1) {
                random_device rd;
                uniform_int_distribution<int> dist(1, issuableReinforcementPool);
                armiesToDeploy = dist(rd);
            }
            Territory *targetTerr = this->toDefend().front(); // owned territory with the lowest number of army units (actual + issued)
            order_list->add(
                    new Deploy(targetTerr, this, armiesToDeploy, game)); // deploy armies to the weakest territory
            issuableReinforcementPool -= armiesToDeploy; // decrement player's reinforcement pool
            targetTerr->set_issued_army_units(
                    targetTerr->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units

            cout << *this << " issued a new deploy order of " << armiesToDeploy << " armies to "
                 << targetTerr->get_name() << endl;
        } else if (!this->hand->getCards().empty()) {
            hand->play(*game->getDeck(), this, 0); // play every card in player's hand
        } else if (advanceAttackOrdersIssued < 2 &&
                   advanceAttackOrdersIssued < toAttack().size()) { // issue at most 2 advance attack orders
            Territory *targetTerr = toAttack().at(advanceAttackOrdersIssued);
            Territory *sourceTerr = strongestOwnedNeighbor(targetTerr);
            // send all source territory army units except 1
            order_list->add(new Advance(sourceTerr, targetTerr, this,
                                        sourceTerr->get_army_units() + sourceTerr->get_issued_army_units(), game));

            advanceAttackOrdersIssued++; // increment orders issued
            cout << *this << " issued a new advance order from " << sourceTerr->get_name() << " to an enemy territory "
                 << targetTerr->get_name() << endl;
        } else if (advanceDefendOrdersIssued < 1 && toDefend().size() > 1) { // issue at most 1 advance defend order
            Territory *targetTerr = toDefend().front(); // weakest owned territory
            Territory *sourceTerr = toDefend().back(); // strongest owned territory
            // send half source territory army units
            order_list->add(new Advance(sourceTerr, targetTerr, this,
                                        (sourceTerr->get_army_units() + sourceTerr->get_issued_army_units()) / 2,
                                        game));

            advanceDefendOrdersIssued++; // increment orders issued
            cout << *this << " issued a new advance order from " << sourceTerr->get_name() << " to their own territory "
                 << targetTerr->get_name() << endl;
        } else {
            cout << *this << " is done issuing orders" << endl;
            this->isDoneIssuingOrders = true;
        }
    }
    else{
        return strategy->issueOrder();
    }
}

//makes the territory exchange between 2 players, when territory gets conquered
void Player::conquerTerritory(Territory* t) {
    Player* loser = t->get_owner();
    loser->removeTerritory(t);
    this->addTerritory(t);
    this->conquerer = true;
}

// let neutral player conquer territory as a result of blockade
void Player::neutralConquerTerritory(Territory* t) {
    Player* loser = t->get_owner();
    loser->removeTerritory(t);
    this->addTerritory(t);
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

// add a friendly player when executing Negotiate order
void Player::addFriendly(int playerID) {
    friendlyList.push_back(playerID);
}

// reset player's friendly list (at the end of every turn)
void Player::resetFriendlyList() {
    friendlyList.clear();
}

// reset conquerer boolean
void Player::resetConquerer() {
    this->conquerer = false;
}

// add a single order to player's order list
void Player::addOrder(Order *o){
    this->order_list->add(o);
}

// *****************************************************************************************************************
// GETTERS
// *****************************************************************************************************************

int Player::getPlayerID() const{
    return this->playerID;
}

PlayerStrategy* Player::getStrategy() const{
    return this->strategy;
}

GameEngine* Player::getGame() const{
    return game;
}

string Player:: getName() const{
    return name;
}

vector<Territory*> Player::getTerritories() const{
    return territories;
}

OrdersList* Player :: getPlayerOrderList() const{
    return order_list;
}

Hand* Player::getHand() const{
    return hand;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

int Player::getIssuableReinforcementPool() const {
    return issuableReinforcementPool;
}
int Player::getAdvanceDefendOrdersIssued() const {
    return advanceDefendOrdersIssued;
}

int Player::getAdvanceAttackOrdersIssued() const {
    return advanceAttackOrdersIssued;
}

bool Player::getIsDoneIssuingOrders() const {
    return this->isDoneIssuingOrders;
}

vector<int> Player::getFriendlyList() const {
    return friendlyList;
}

bool Player::getConquerer() const {
    return conquerer;
}

int Player::getNumTerritories() const {
    return this->getTerritories().size();
}

// *****************************************************************************************************************
// SETTERS
// *****************************************************************************************************************

void Player::setStrategy(PlayerStrategy* newStrategy) {
    if(this->strategy != nullptr) {
        delete this->strategy;
    }
    this->strategy = newStrategy;
}

void Player::setGame(GameEngine* game) {
    this->game = game;
}

void Player::setTerritories(vector<Territory*> t){
    this->territories = t;
}

void Player::setPlayerOrderList(OrdersList* orders){
    this->order_list = orders;
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