#pragma once
#include <vector>
using std::vector;
#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include "../Orders/Orders.h"
#include "../Player/Player.h"

// Card Class
class Card{
public:
    // Number of card instances counter
    static int numCreatedCards;
    // Default Constructor
    Card();
    // Copy Constructor
    Card(const Card& c);
    // Assignment Operator
    Card& operator =(const Card& c);
    // Destructor
    virtual ~Card();
    // Clone method for dynamic copies
    virtual Card* clone() = 0;
    // Virtual play method to be overridden by subclasses
    virtual void play(Player *player) = 0;
    // Getters
    virtual string getCardType() = 0;
    int getId() const;
private:
    const static string cardType;
    int id;
};
// Stream insertion operator
ostream& operator<<(ostream& os, Card& c);

// Card Type Subclass
class BombCard : public Card{
public:
    // Default Constructor
    BombCard();
    // Copy Constructor
    BombCard(const BombCard& b);
    // Destructor
    ~BombCard();
    // Clone method for dynamic copies
    Card* clone();
    // Play method to return add corresponding order to Player's orders list
    void play(Player *player);
    // Getter
    string getCardType();
private:
    const static string cardType;
};

// Card Type Subclass
class ReinforcementCard : public Card{
public:
    // Default Constructor
    ReinforcementCard();
    // Copy Constructor
    ReinforcementCard(const ReinforcementCard& r);
    // Destructor
    ~ReinforcementCard();
    // Clone method for dynamic copies
    Card* clone();
    // Play method to return add corresponding order to Player's orders list
    void play(Player *player);
    // Getter
    string getCardType();
private:
    const static string cardType;
};
// Stream insertion operator
ostream& operator<<(ostream& os, ReinforcementCard& c);

// Card Type Subclass
class BlockadeCard : public Card{
public:
    // Default Constructor
    BlockadeCard();
    // Copy Constructor
    BlockadeCard(const BlockadeCard& b);
    // Destructor
    ~BlockadeCard();
    // Clone method for dynamic copies
    Card* clone();
    // Play method to return add corresponding order to Player's orders list
    void play(Player *player);
    // Getter
    string getCardType();
private:
    const static string cardType;
};
// Stream insertion operator
ostream& operator<<(ostream& os, BlockadeCard& c);

// Card Type Subclass
class AirliftCard : public Card{
public:
    // Default Constructor
    AirliftCard();
    // Copy Constructor
    AirliftCard(const AirliftCard& a);
    // Destructor
    ~AirliftCard();
    // Clone method for dynamic copies
    Card* clone();
    // Play method to return add corresponding order to Player's orders list
    void play(Player *player);
    // Getter
    string getCardType();
private:
    const static string cardType;
};
// Stream insertion operator
ostream& operator<<(ostream& os, AirliftCard& c);

// Card Type Subclass
class DiplomacyCard : public Card{
public:
    // Default Constructor
    DiplomacyCard();
    // Copy Constructor
    DiplomacyCard(const DiplomacyCard& d);
    // Destructor
    ~DiplomacyCard();
    // Clone method for dynamic copies
    Card* clone();
    // Play method to return add corresponding order to Player's orders list
    void play(Player *player);
    // Getter
    string getCardType();
private:
    const static string cardType;
};
// Stream insertion operator
ostream& operator<<(ostream& os, DiplomacyCard& c);

// Deck Class
class Deck
{
public:
    // Default Constructor
    Deck();
    // Parameterized constructor initializes deck with vector of cards
    Deck(vector<Card *>& cards);
    // Copy Constructor
    Deck(const Deck& d);
    // Assignment Operator
    Deck& operator =(const Deck& d);
    // Destructor
    ~Deck();
    // Draw method removes card from the deck and adds it to the players hand
    void draw(Player& p);
    void drawStrategy(Player &p);
    // method to check if drawn card is acceptable for player strategy
    bool acceptCard(string ps, string cardType);
    // Checks if deck is empty
    bool isEmpty();
    // Getter
    vector<Card *> &getCards();

private:
    vector<Card *> cards;
};
// Stream insertion operator
ostream& operator << (ostream& os, Deck& d);

// Hand Class
class Hand
{
public:
    // Default Constructor
    Hand();
    // Copy Constructor
    Hand(const Hand& h);
    // Assignment Operator
    Hand& operator=(const Hand& h);
    // Destructor
    ~Hand();
    // Adds passed Card to Hand
    void addCard(Card *c);
    // Removes card at index from Hand and adds it to the Deck
    void play(Deck &d, Player *player, int index);
    // Getter
    vector<Card *> &getCards();
    // Checks if Hand is empty
    bool isEmpty();

private:
    vector<Card *> cards;
};
// Stream insertion operator
ostream& operator << (ostream& os, Hand& h);


