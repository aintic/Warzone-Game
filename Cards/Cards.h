#pragma once
#include <vector>
using std::vector;
#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include "../Orders/Orders.h"
#include "../Player/Player.h"

//class Deck;
//class Hand;
class Card{
public:
    static int numCreatedCards;
    Card();
    Card(const Card& c);
    Card& operator =(const Card& c);
    virtual ~Card();
    virtual Card* clone() = 0;
    //virtual bool transfer(Hand &aHand, Deck &aDeck, int index);
    virtual Order* play() = 0;
    virtual string getCardType() = 0;
    int getId() const;
private:
    const static string cardType;
    int id;
};
ostream& operator<<(ostream& os, Card& c);


class BombCard : public Card{
public:
    BombCard();
    BombCard(const BombCard& b);
    Card* clone();
    Order* play();
    string getCardType();
private:
    const static string cardType;
};


class ReinforcementCard : public Card{
public:
    ReinforcementCard();
    ReinforcementCard(const ReinforcementCard& r);
    Card* clone();
    Order* play();
    string getCardType();
private:
    const static string cardType;
};


class BlockadeCard : public Card{
public:
    BlockadeCard();
    BlockadeCard(const BlockadeCard& b);
    Card* clone();
    Order* play();
    string getCardType();
private:
    const static string cardType;
};


class AirliftCard : public Card{
public:
    AirliftCard();
    AirliftCard(const AirliftCard& a);
    Card* clone();
    Order* play();
    string getCardType();
private:
    const static string cardType;
};


class DiplomacyCard : public Card{
public:
    DiplomacyCard();
    DiplomacyCard(const DiplomacyCard& d);
    Card* clone();
    Order* play();
    string getCardType();
private:
    const static string cardType;
};

class Deck
{
public:
    Deck();
    Deck(vector<Card *>& cards);
    Deck(const Deck& d);
    Deck& operator =(const Deck& d);
    ~Deck();
    Card* draw(Player& p);
    bool isEmpty();
    vector<Card *> &getCards();

private:
    vector<Card *> cards;
};

ostream& operator << (ostream& os, Deck& d);

class Hand
{
public:
    Hand();
    Hand(const Hand& h);
    Hand& operator=(const Hand& h);
    ~Hand();
    void addCard(Card *c);
    Order* play(Deck& d,  int index);
    vector<Card *> &getCards();
    bool isEmpty();

private:
    vector<Card *> cards;
};
ostream& operator << (ostream& os, Hand& h);


