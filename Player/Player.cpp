#include "Player.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include <random>
using namespace std;

/**
 * Default constructor for Player
 **/
Player::Player() {
    this->playerID = 0;
    this->name = "player";
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand;
    this->order_list = new OrdersList;
}
/**
 * Constructor: Construct a new Player object
 *
 * @param playerID
 * @param name
 */

Player::Player(int playerID, string name) {
    this->playerID = playerID;
    this->name = name;
    vector<Territory*> t;
    this->territories = t;
    this->hand = new Hand();
    this->order_list = new OrdersList();
}

/**
 * Constructor: Construct a new Player object
 *
 * @param playerID
 * @param name
 * @param territories
 * @param hand
 * @param orders
 */

//Constructor with player id, territories, hand and orders
//So, the player owns territories, owns hand cards and list of orders


Player::Player(int playerID, string name, vector<Territory*>& territories, Hand* hand, OrdersList* orders) {
    this->playerID = playerID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
}

/**
 * Copy constructor : Construct a new Player object
 *
 * @param p
 */
Player::Player(const Player& p){
    playerID = p.playerID;
    name = p.name;
    for (Territory* t : p.territories){
        this->addTerritory(new Territory(*t));
    }
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
}

/**
 * Destructor : Destruct Player
 */
Player::~Player()
{
    delete hand;
    delete order_list;
    for (Territory* t : territories){
        delete t;
    }
    territories.clear();
}


/**
 * Assignment operator
 * @param p
 * @return Player&
 */
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

/**
 * toDefend : returns a list of territories to be defended
 * @return
 */
vector<Territory*> Player:: toDefend(){
    return this->territories;
}
/**
 * toAttack : returns a list of territories to be attacked
 * @return
 */
vector<Territory*> Player:: toAttack(){
    return this->territories;

}

void Player::issueOrder(Order* o) {
    if(o) {
        this->order_list->add(o);
    }
}

/**
 * issueOrder: creates an order object and adds it to the list of orders
 * when an issue is created then Player object sets player's orderlist and it executes it
 * @param p
 */
void Player::issueOrder(){
    Order* o[] = {new Deploy, new Advance,new BombCardOrder, new BlockadeCardOrder, new AirliftCardOrder,new Negotiate};
    random_device rd;
    uniform_int_distribution<int> dist(0, 5);
    int randomIndex = dist(rd);
    order_list->add(o[randomIndex]);

}
/**
 * addTerritory: it adds territories to each object
 * @param t
 */
void Player::addTerritory(Territory* t){
    territories.push_back(t); // can be used like p1->addTerritory(t1*)
}

//getters
int Player::getPlayerID(){
    return playerID;
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

//setters
void Player::setPlayerOrderList(OrdersList* orders){
    this->order_list = orders;
}

void Player::setTerritories(vector<Territory*> t){
    this->territories = t;
}

ostream& operator << (ostream& os, Player& p){
    return os << "Name: " << p.getName() << " ID: " << p.getPlayerID();
}

