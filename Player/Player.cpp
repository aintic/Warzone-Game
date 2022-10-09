#include "Player.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
using namespace std;

/**
 * Default constructor for Player
 **/
Player::Player() {
    int playerID;
    string name;
    vector<Territory*> territories;
    vector<Territory*> territoriesOwnedByPlayer;
    this->hand = new Hand();
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
    vector<Territory*> territories;
    vector<Territory*> territoriesOwnedByPlayer;
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


Player::Player(int playerID, string name, vector<Territory*> territories, Hand* hand, OrdersList* orders) {
    this->playerID = playerID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
    this->territoriesOwnedByPlayer = territoriesOwnedByPlayer;
}

/**
 * Copy constructor : Construct a new Player object
 *
 * @param p
 */
Player::Player(const Player& p){
        playerID = p.playerID;
        name = p.name;
        territories = p.territories;
        this->hand = new Hand(*(p.hand));
        this->order_list = new OrdersList(*(p.order_list));
        territoriesOwnedByPlayer = p.territoriesOwnedByPlayer;
    }

/**
 * Destructor : Destruct Player
 */
Player::~Player()
{
    delete hand;
    delete order_list;
    territoriesOwnedByPlayer.clear();
    name.clear();

}


/**
 * Assignment operator
 * @param p
 * @return Player&
 */
Player& Player::operator=(const Player& p){
    playerID = p.playerID;
    name = p.name;
    territories = p.territories;
    this->hand = new Hand(*(p.hand));
    this->order_list = new OrdersList(*(p.order_list));
    territoriesOwnedByPlayer = p.territoriesOwnedByPlayer;
    return *this;
    }




/**
 * toDefend : returns a list of territories to be defended
 * @return
 */
vector<Territory*> Player:: toDefend(){
    return this->territoriesOwnedByPlayer;
}
/**
 * toAttack : returns a list of territories to be attacked
 * @return
 */
vector<Territory*> Player:: toAttack(){
    return this->territoriesOwnedByPlayer;

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
void Player:: issueOrder(){

    Order* testDeploy = new Deploy;
    Order* testAdvance = new Advance;
    Order* testBomb = new BombCardOrder;
    Order* testBlockade = new BlockadeCardOrder;
    Order* testAirlift = new AirliftCardOrder;
    Order* testNegotiate = new Negotiate;

    OrdersList* ol = new OrdersList;


    cout << "\nAdd orders.\n" << endl;
    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);

    //ol->executeList();

    setPlayerOrderList(ol); //set orderlist

}
/**
 * addTerritory: it adds territories to each object
 * @param t
 */
void Player::addTerritory(Territory* t){
    territoriesOwnedByPlayer.push_back(t); // can be used like p1->addTerritory(t1*)
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
OrdersList* Player :: setPlayerOrderList(OrdersList* orders){
    this->order_list = orders;
}
