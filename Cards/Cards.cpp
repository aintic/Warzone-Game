#include "Cards.h"
#include <string>
#include <iostream>
#include <random>
using namespace std;

// Card Class
int Card::numCreatedCards = 0;

Card::Card() {
    this->id = ++numCreatedCards;
}

Card::Card(const Card& c){
    this->id = c.id;
}

Card::~Card() = default;

bool Card::transfer(Hand &aHand, Deck &aDeck, int index){
    if(index >= 0 && index < aHand.getCards().size()){
        aDeck.getCards().push_back(aHand.getCards().at(index));
        aHand.getCards().erase(aHand.getCards().begin() + index);
        return true;
    }
    return false;
}

int Card::getId() const{
    return id;
}

string Card::getName() const{
    return name;
}

Card& Card::operator=(const Card& c){
    if(this != &c){
        this->id = c.id;
    }
    return *this;
}

ostream& operator<<(ostream& os, Card& c){
    os << "card " << c.getId() << ": " << c.getName();
    return os;
}



// Bomb Class
Bomb::Bomb() : Card(){
    this->name = "Bomb";
}

Bomb::Bomb(const Bomb& b) : Card(b){
    this->name = b.name;
}

Card* Bomb::clone() {
    return new Bomb(*this);
}

void Bomb::play(){}



// Reinforcement Class
Reinforcement::Reinforcement() : Card(){
    this->name = "Reinforcement";
}

Reinforcement::Reinforcement(const Reinforcement& r) : Card(r){
    this->name = r.name;
}

Card* Reinforcement::clone() {
    return new Reinforcement(*this);
}

void Reinforcement::play(){}



// Blockade Class
Blockade::Blockade() : Card(){
    this->name = "Blockade";
}

Blockade::Blockade(const Blockade& b) : Card(b){
    this->name = b.name;
}

Card* Blockade::clone() {
    return new Blockade(*this);
}

void Blockade::play() {}



// Airlift Class
Airlift::Airlift() : Card(){
    this->name = "Airlift";
}

Airlift::Airlift(const Airlift& a) : Card(a){
    this->name = a.name;
}

Card* Airlift::clone() {
    return new Airlift(*this);
}

void Airlift::play() {}



// Diplomacy Class
Diplomacy::Diplomacy() :Card(){
    this->name = "Diplomacy";
}

Diplomacy::Diplomacy(const Diplomacy& d) : Card(d){
    this->name = name;
}

Card* Diplomacy::clone(){
    return new Diplomacy(*this);
}

void Diplomacy::play() {}



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
        this->cards.push_back(new Bomb());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new Reinforcement());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new Blockade());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new Airlift());
    }
    for (int i = 0; i < 3; i++){
        this->cards.push_back(new Diplomacy());
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

Card* Deck::draw(Hand &aHand){
    if (!cards.empty()){
        random_device rd;
        uniform_int_distribution<int> dist(0, cards.size() - 1);
        int randomIndex = dist(rd);
        aHand.getCards().push_back(this->getCards().at(randomIndex));
        this->cards.erase(this->cards.begin() + randomIndex);
        return aHand.getCards().back();
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