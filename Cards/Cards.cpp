#include "Cards.h"
#include <string>
#include <iostream>
#include <random>
#include "../Orders/Orders.h"
#include "../Player/Player.h"
using namespace std;

const string BombCard::cardType = "Bomb";
const string ReinforcementCard::cardType = "Reinforcement";
const string BlockadeCard::cardType = "Blockade";
const string AirliftCard::cardType = "Airlift";
const string DiplomacyCard::cardType = "Negotiate";


// Card Class
int Card::numCreatedCards = 0;

Card::Card() {
    this->id = ++numCreatedCards;
}

Card::Card(const Card& c){
    this->id = c.id;
}

Card::~Card() = default;

//bool Card::transfer(Hand &aHand, Deck &aDeck, int index){
//    if(index >= 0 && index < aHand.getCards().size()){
//        aDeck.getCards().push_back(aHand.getCards().at(index));
//        aHand.getCards().erase(aHand.getCards().begin() + index);
//        return true;
//    }
//    return false;
//}

int Card::getId() const{
    return id;
}

Card& Card::operator=(const Card& c){
    if(this != &c){
        this->id = c.id;
    }
    return *this;
}

ostream& operator<<(ostream& os, Card& c){
    os << "card " << c.getId() << ": " << c.getCardType();
    return os;
}



// BombCardOrder Class
BombCard::BombCard() : Card(){}

BombCard::BombCard(const BombCard& b) : Card(b){}

Card* BombCard::clone() {
    return new BombCard(*this);
}

Order* BombCard::play(){
    return new BombCardOrder;
}

string BombCard::getCardType() {
    return cardType;
}



// ReinforcementCard Class
ReinforcementCard::ReinforcementCard() : Card(){}

ReinforcementCard::ReinforcementCard(const ReinforcementCard& r) : Card(r){}

Card* ReinforcementCard::clone() {
    return new ReinforcementCard(*this);
}

Order* ReinforcementCard::play(){
    return nullptr;
}

string ReinforcementCard::getCardType() {
    return cardType;
}



// BlockadeCardOrder Class
BlockadeCard::BlockadeCard() : Card(){}

BlockadeCard::BlockadeCard(const BlockadeCard& b) : Card(b){}

Card* BlockadeCard::clone() {
    return new BlockadeCard(*this);
}

Order* BlockadeCard::play() {
    return new BlockadeCardOrder;
}

string BlockadeCard::getCardType() {
    return cardType;
}



// AirliftCardOrder Class
AirliftCard::AirliftCard() : Card(){}

AirliftCard::AirliftCard(const AirliftCard& a) : Card(a){}

Card* AirliftCard::clone() {
    return new AirliftCard(*this);
}

Order* AirliftCard::play() {
    return new AirliftCardOrder;
}

string AirliftCard::getCardType() {
    return cardType;
}



// DiplomacyCard Class
DiplomacyCard::DiplomacyCard() : Card(){}

DiplomacyCard::DiplomacyCard(const DiplomacyCard& d) : Card(d){}

Card* DiplomacyCard::clone(){
    return new DiplomacyCard(*this);
}

Order* DiplomacyCard::play() {
    return new Negotiate;
}

string DiplomacyCard::getCardType() {
    return cardType;
}




// Hand Class
Hand::Hand(){
    vector<Card *> c;
    this->cards = c;
}

Hand::Hand(const Hand& h){
    for(Card *c : h.cards){
        this->cards.push_back(c->clone());
    }
}

Hand::~Hand() {
    for (Card* c : this->cards){
        delete c;
    }
}

void Hand::addCard(Card *c){
    this->cards.push_back(c);
}

Order* Hand::play(Deck& d, int index){
    Order* o = nullptr;
        if(index >= 0 && index < this->cards.size()){
            o = this->cards.at(index)->play();
            d.getCards().push_back(this->cards.at(index));
            this->cards.erase(this->cards.begin() + index);
        }
        else{
            cout << "Play failed - Invalid Index: " << index;
        }
        return o;
    }

vector<Card *> &Hand::getCards(){
    return this->cards;
}

bool Hand::isEmpty(){
    return this->cards.empty();
}

Hand& Hand::operator=(const Hand& h) {
    if (this != &h) {
        for (Card *c: h.cards) {
            this->cards.push_back(c->clone());
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, Hand& h){
    int numCards = h.getCards().size();
    for (int i = 0; i < numCards; i++){
        if (i !=  numCards - 1){
            os << *h.getCards().at(i) << ", ";
        }
        else {
            os << *h.getCards().at(i);
        }
    }
    return os;
}



//Deck Class
Deck::Deck(){
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new BombCard());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new ReinforcementCard());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new BlockadeCard());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new AirliftCard());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new DiplomacyCard());
    }
}

Deck::Deck(vector<Card *>& cards){
    this->cards = cards;
}

Deck::Deck(const Deck &d){
    for (Card *c : d.cards){
        this->cards.push_back(c->clone());
    }
}

Deck::~Deck() {
    for(Card* c : this->cards){
        delete c;
    }
}

Card* Deck::draw(Player& p){
    if (!cards.empty()){
        random_device rd;
        uniform_int_distribution<int> dist(0, cards.size() - 1);
        int randomIndex = dist(rd);
        p.getHand()->getCards().push_back(this->getCards().at(randomIndex));
        this->cards.erase(this->cards.begin() + randomIndex);
        return p.getHand()->getCards().back();
    }
    else{
        cout << "Draw Failed: Deck is Empty";
    }
    return nullptr;
}

bool Deck::isEmpty(){
    return this->cards.empty();
}

vector<Card*> &Deck::getCards(){
    return this->cards;
}

Deck& Deck::operator=(const Deck &d){
    for (Card* c : d.cards){
        this->cards.push_back(c->clone());
    }
    return *this;
}

ostream& operator <<(ostream& os, Deck& d){
    os << "Deck: " << endl;
        if (d.getCards().empty()){
            os << "deck is empty" << endl;
        } else{

        for (Card* c : d.getCards()) {
            os << *c << endl;
        }
        return os;
    }
}