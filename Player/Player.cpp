#include "Player.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "algorithm"
using std::find_if;


int Player::uniqueID = 0;

//Default constructor
Player::Player() {
    this->playerID = ++uniqueID;
    this->name = "player";
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand;
    this->order_list = new OrdersList();
    this->reinforcementPool = 5;
    vector<int> f;
    this->_friendlyList = f;
    this->conquerer = false;
}

//Constructor with name only
Player::Player(string name) {
    this->playerID = ++uniqueID;
    this->name = name;
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand();
    this->order_list = new OrdersList();
    vector<int> f;
    this->_friendlyList = f;
    this->conquerer = false;
}


//Constructor with player id, territories, hand and orders
//So, the player owns territories, owns hand cards, list of orders and list of friendly players negotiated with
Player::Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders) {
    this->playerID = ++uniqueID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
    vector<int> f;
    this->_friendlyList = f;
    this->conquerer = false;
}

//copy constructor
Player::Player(const Player& p){
    playerID = getPlayerID();
    name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
    this->_friendlyList = p._friendlyList;
    this->conquerer = p.conquerer;
}

//destructor
Player::~Player()
{
    delete hand;
    delete order_list;
    territories.clear();
    _friendlyList.clear();
}

//assignment operator
Player& Player::operator=(const Player& p){
    playerID = p.playerID;
    name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
    this->_friendlyList = p._friendlyList;
    this->conquerer = p.conquerer;
    return *this;
}

//returns a list of territories to be defended
vector<Territory*> Player:: toDefend(){
    return this->territories;
}

//returns a list of territories to be attacked
vector<Territory*> Player:: toAttack(){
    vector<Territory*> toAttackTerritories;
    for (Territory *ownedTerritory : territories){
        for (Territory *neighborTerritory : ownedTerritory->get_neighbours()) {
            if (neighborTerritory->get_owner() != this) {
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) {
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    return toAttackTerritories;
}

void Player::addOrder(Order *o){
    this->order_list->add(o);
}

//creates an order object and adds it to the list of orders
bool Player::issueOrder(Deck *deck) {
    if(reinforcementPool != 0) {
        order_list->add(new Deploy);
        cout << *this << " issued a new deploy order" << endl;
        reinforcementPool--;
    }
    else if (!this->hand->getCards().empty()) {
        hand->play(*deck, this, 0);
    }
    else {
        order_list->add(new Advance);
        cout << *this << " issued a new advance order" << endl;
        cout << *this << " is done issuing orders" << endl;
        return false;
    }
    return true;
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

// add a friendly player when executing Negotiate order
void Player::addFriendly(int playerID) {
    _friendlyList.push_back(playerID);
}

// reset player's friendly list (at the end of every turn)
void Player::resetFriendlyList() {
    _friendlyList.clear();
}

// check if a player is friendly to current player
bool Player::isFriendly(int playerID) {
    int size = _friendlyList.size();

    for (int i = 0; i < size; i++) {
        if (_friendlyList[i] == playerID) {
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
void Player::setPlayerOrderList(OrdersList* orders){
    this->order_list = orders;
}

void Player::setTerritories(vector<Territory*> t){
    this->territories = t;
}

void Player::setReinforcementPool(int armies) {
    this->reinforcementPool = armies;
}

ostream& operator<<(ostream& os, Player& p){
    return os << "Name: " << p.getName() << ", ID: " << p.getPlayerID();
}





