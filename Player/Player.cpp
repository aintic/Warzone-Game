#include "Player.h"



using namespace std;

//Constructor with player id, territories, hand and orders

//So, the player owns territories, owns hand cards and list of orders

Player::Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<Order*> orders) {
    this->playerID = playerID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->orders = orders;
}







// toDefend() - returns a list of territories that are to be defended
vector<Territory*> Player:: toDefend(){


}
// toAttack() - returns a list of territories that are to be attacked
vector<Territory*> Player:: toAttack(){

}

void issueOrder(){
}
















//getters

int Player::getPlayerID(){
    return playerID;
}
Hand* Player::getHand(){
    return hand;
}
vector<Order*> Player :: getPlayerOrders(){
    return orders;
}

vector<Territory*> Player::getTerritories(){
    return territories;
}
