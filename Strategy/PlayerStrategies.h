#pragma once
#include <vector>
#include "Player.h"
using std::vector;

class Territory;

class PlayerStrategy {

public:
    PlayerStrategy(); // Default constructor
    PlayerStrategy(const Player& p); // Copy constructor
    PlayerStrategy& operator=(const PlayerStrategy&); // Assignment operator
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
    NeutralPlayerStrategy(Player* player);
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
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
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
private:
    const static string strategyName;
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