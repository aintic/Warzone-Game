#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::ostream;

class Territory;
class Player;

class PlayerStrategy {

public:
    PlayerStrategy(); // Default constructor
    PlayerStrategy(const PlayerStrategy& ps); // Copy constructor
    PlayerStrategy(Player *p);
    PlayerStrategy& operator=(const PlayerStrategy& ps); // Assignment operator
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const PlayerStrategy& ps);
    Player* getPlayer(); // Player getters and setters
    void setPlayer(Player*);
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual string getStrategyName() const = 0;

protected:
    Player* player;
};


class NeutralPlayerStrategy : public PlayerStrategy{

public:
    //default constructor
    NeutralPlayerStrategy(Player* player);
    NeutralPlayerStrategy(const NeutralPlayerStrategy& neutralPlayerStrategy); // Copy constructor
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const NeutralPlayerStrategy& nps);
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& neutralPlayerStrategy); // Assignment operator

private:
    const static string strategyName;
};


class CheaterPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;

private:
    const static string strategyName;
};


class HumanPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
private:
    const static string strategyName;
};


class AggressivePlayerStrategy : public PlayerStrategy{

public:
    AggressivePlayerStrategy(Player* player);
    AggressivePlayerStrategy(const AggressivePlayerStrategy &aps);
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy &aps);
    // stream insertion operator
    friend ostream& operator << (ostream& out,  const AggressivePlayerStrategy& aps);
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    Territory* terrMostSurroundedByEnemies() const;
    int getAirliftCardIssued() const;
    void setAirliftCardIssued(int airliftCardIssued);
    bool targetIsAdjacent(Territory *source, Territory *target) const;
private:
    const static string strategyName;
    int airliftCardIssued;
};


class BenevolentPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
private:
    const static string strategyName;
};