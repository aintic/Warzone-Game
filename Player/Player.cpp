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
    return this->strategy->toDefend();
}

//returns a list of territories to be attacked
vector<Territory*> Player:: toAttack(){
    return this->strategy->toAttack();
}

//creates an order object and adds it to the list of orders
void Player::issueOrder() {
    return this->strategy->issueOrder();
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

