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
}

//Constructor with name only
Player::Player(string name) {
    this->playerID = ++uniqueID;
    this->name = name;
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand();
    this->order_list = new OrdersList();
}


//Constructor with player id, territories, hand and orders
//So, the player owns territories, owns hand cards and list of orders
Player::Player(string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders) {
    this->playerID = ++uniqueID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
}

//copy constructor
Player::Player(const Player& p){
    playerID = getPlayerID();
    name = p.name;
    for (Territory* t : p.territories){
        this->addTerritory(new Territory(*t));
    }
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
}

//destructor
Player::~Player()
{
    delete hand;
    delete order_list;
    for (Territory* t : territories){
        delete t;
    }
    territories.clear();
}

//assignment operator
Player& Player::operator=(const Player& p){
    playerID = p.playerID;
    name = p.name;
    for (Territory* t : p.territories){
        this->addTerritory(new Territory(*t));
    }
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
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
    return os << "Name: " << p.getName() << " ID: " << p.getPlayerID();
}





