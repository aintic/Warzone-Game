#ifndef COMP_345_CARDS_H
#define COMP_345_CARDS_H
#include <vector>
using std::vector;
#include <iostream>
using std::ostream;
#include <string>
using std::string;

class Deck;
class Hand;
class Card{
public:
    static int numCreatedCards;
    Card();
    Card(const Card& c);
    Card& operator =(const Card& c);
    virtual ~Card();
    virtual Card* clone() = 0;
    virtual bool transfer(Hand &aHand, Deck &aDeck, int index);
    virtual void play() = 0;
    int getId() const;
    string getName() const;
protected:
    string name;
private:
    int id;
};
ostream& operator<<(ostream& os, Card& c);


class Bomb : public Card{
public:
    Bomb();
    Bomb(const Bomb& b);
    Card* clone();
    void play();
};


class Reinforcement : public Card{
public:
    Reinforcement();
    Reinforcement(const Reinforcement& r);
    Card* clone();
    void play();
};


class Blockade : public Card{
public:
    Blockade();
    Blockade(const Blockade& b);
    Card* clone();
    void play();
};


class Airlift : public Card{
public:
    Airlift();
    Airlift(const Airlift& a);
    Card* clone();
    void play();
};


class Diplomacy : public Card{
public:
    Diplomacy();
    Diplomacy(const Diplomacy& d);
    Card* clone();
    void play();
};


class Hand
{
public:
    Hand();
    Hand(const Hand& h);
    Hand& operator=(const Hand& h);
    ~Hand();
    void addCard(Card *c);
    vector<Card *> &getCards();
    bool isEmpty();

private:
    vector<Card *> cards;
};
ostream& operator << (ostream& os, Hand& h);


class Deck
{
public:
    Deck();
    Deck(vector<Card *>& cards);
    Deck(const Deck& d);
    Deck& operator =(const Deck& d);
    ~Deck();
    Card* draw(Hand &aHand);
    bool isEmpty();
    vector<Card *> &getCards();

private:
    vector<Card *> cards;
};

ostream& operator << (ostream& os, Deck& d);
#endif //COMP_345_CARDS_H
