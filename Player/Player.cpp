
#include "Player.h"
#include "Orders.h"



using namespace std;





/**
 * Default constructor for Player
 **/
Player::Player() {
    this->playerID = 0;
    this->name = "p1";
    this->territories = territories;
    this->territoriesOwnedByPlayer = territoriesOwnedByPlayer;
    this->hand = hand;
    this->order_list = order_list;
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
    this->territories = territories;
    this->territoriesOwnedByPlayer = territoriesOwnedByPlayer;
    this->hand = hand;
    this->order_list = order_list;
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
        hand = p.hand;
        order_list = p.order_list;
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
    hand = p.hand;
    order_list = p.order_list;
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
/**
 * issueOrder: creates an order object and adds it to the list of orders
 * when an issue is created then Player object sets player's orderlist and it executes it
 * @param p
 */
void Player:: issueOrder(Player* p){
    cout << p->name <<  " Adds order" << endl; //Indicate which player is issuing orders
    Order* testDeploy = new Deploy;
    Order* testAdvance = new Advance;
    Order* testBomb = new Bomb;
    Order* testBlockade = new Blockade;
    Order* testAirlift = new Airlift;
    Order* testNegotiate = new Negotiate;

    OrdersList* ol = new OrdersList;


    cout << "\nAdd orders.\n" << endl;
    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);
    cout << "ExecuteList" << endl;
    //ol->executeList();

    setPlayerOrderList(ol);

    p->order_list->executeList(); //it executes each player's orderlist
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
