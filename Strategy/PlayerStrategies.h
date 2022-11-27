#pragma once
#include <vector>

using std::vector;

class Territory;

class PlayerStrategy {

public:
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttach() = 0;
    virtual vector<Territory*> toDefend() = 0;
};


class NeutralPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttach() override;
    vector<Territory*> toDefend() override;
};


class CheaterPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttach() override;
    vector<Territory*> toDefend() override;
};


class HumanPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttach() override;
    vector<Territory*> toDefend() override;
};


class AggressivePlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttach() override;
    vector<Territory*> toDefend() override;
};


class BenevolentPlayerStrategy : public PlayerStrategy{

public:
    void issueOrder() override;
    vector<Territory*> toAttach() override;
    vector<Territory*> toDefend() override;
};