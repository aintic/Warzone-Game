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
    PlayerStrategy(Player *p); // Parametized constructor
    PlayerStrategy(const PlayerStrategy& ps); // Copy constructor
    PlayerStrategy& operator=(const PlayerStrategy& ps); // Assignment operator
    friend ostream& operator << (ostream& out,  const PlayerStrategy& ps); // stream insertion operator
    virtual ~PlayerStrategy();
    Player* getPlayer(); // Player getter
    void setPlayer(Player*); // Player setter
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual string getStrategyName() const = 0;
    virtual PlayerStrategy* clone() const = 0;

protected:
    Player* player;
};


class NeutralPlayerStrategy : public PlayerStrategy{

public:
    NeutralPlayerStrategy(); // default constructor
    NeutralPlayerStrategy(Player* player); // parametized constructor
    NeutralPlayerStrategy(const NeutralPlayerStrategy& neutralPlayerStrategy); // Copy constructor
    ~NeutralPlayerStrategy() override;
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& neutralPlayerStrategy); // Assignment operator
    friend ostream& operator << (ostream& out,  const NeutralPlayerStrategy& nps); // stream insertion operator
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    NeutralPlayerStrategy* clone() const override;
private:
    const static string strategyName;
};


class CheaterPlayerStrategy : public PlayerStrategy{

public:
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player);
    CheaterPlayerStrategy(const CheaterPlayerStrategy &cps);
    CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy &cps);
    ~CheaterPlayerStrategy() override;
    friend ostream& operator << (ostream& os,  const CheaterPlayerStrategy& cps);
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    CheaterPlayerStrategy* clone() const override;
private:
    const static string strategyName;
};


class HumanPlayerStrategy : public PlayerStrategy{

public:
    HumanPlayerStrategy(); // default constructor
    HumanPlayerStrategy(Player* player); // parametized constructor
    HumanPlayerStrategy(const HumanPlayerStrategy& humanPlayerStrategy); // Copy constructor
    ~HumanPlayerStrategy() override;
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy& humanPlayerStrategy); // Assignment operator
    friend ostream& operator << (ostream& out,  const HumanPlayerStrategy& nps); // stream insertion operator
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    HumanPlayerStrategy* clone() const override;
private:
    const static string strategyName;
};


class AggressivePlayerStrategy : public PlayerStrategy{

public:
    AggressivePlayerStrategy(); // default constructor
    AggressivePlayerStrategy(Player* player); // parametized constructor
    AggressivePlayerStrategy(const AggressivePlayerStrategy &aps); // copy constructor
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy &aps); // assignment operator
    ~AggressivePlayerStrategy() override;
    friend ostream& operator << (ostream& out,  const AggressivePlayerStrategy& aps); // stream insertion operator
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    AggressivePlayerStrategy* clone() const override;
    int getAirliftCardIssued() const;
    void setAirliftCardIssued(int airliftCardIssued);
private:
    const static string strategyName;
    int airliftCardIssued;
    Territory* terrMostSurroundedByEnemies() const;
    bool targetIsAdjacent(Territory *source, Territory *target) const;
};


class BenevolentPlayerStrategy : public PlayerStrategy{

public:
    BenevolentPlayerStrategy(); // default constructor
    explicit BenevolentPlayerStrategy(Player* p); // parametrized constructor
    ~BenevolentPlayerStrategy() override; // destructor
    BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy &bps); // assignment operator
    friend ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& bps); // stream insertion operator
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    string getStrategyName() const override;
    BenevolentPlayerStrategy* clone() const override;
private:
    const static string strategyName;
};