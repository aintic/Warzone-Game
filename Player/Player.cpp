#include "Player.h"



using namespace std;


//defualt constructor
Player::Player() {
    int playerID = 0;
    string name = "p1";
    vector<Territory*> territories;
    vector<Territory*> territoriesOwnedByPlayer; //territoriesOwned byPlayer
    Hand* hand;
    vector<Order*> orders;
}

//Constructor with player id, territories, hand and orders

//So, the player owns territories, owns hand cards and list of orders

Player::Player(int playerID, string name, vector<Territory*> territories, Hand* hand, vector<Order*> orders) {
    this->playerID = playerID;
    this->name = name;
    this->territories = territories;
    this->hand = hand;
    this->order_list = orders;
    vector<Territory*> territoriesOwnedByPlayer;
}







// toDefend() - returns a list of territories that are to be defended
vector<Territory*> Player:: toDefend(){
    return this->territoriesOwnedByPlayer;
}
// toAttack() - returns a list of territories that are to be attacked
vector<Territory*> Player:: toAttack(){

}

void Player:: issueOrder(string order){

    //Order *o= new Order(order); //create an order object


    //order_list.push_back(o); //add it to the list of orders

}

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
vector<Order*> Player :: getPlayerOrderList(){
    return order_list;
}

vector<Territory*> Player::getTerritories(){
    return territories;
}
