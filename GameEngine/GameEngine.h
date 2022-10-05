#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ostream;
using std::endl;



//
//GAME ENGINE CLASS
//
class GameEngine {
private:
    class State* currentState;

public:
    GameEngine();
    State* getCurrentState();
    void setCurrentState(State* state);
    void nextState(State* nextState);

    static int turn;
};


//
//ABSTRACT STATE CLASS
//
class State{
protected:
    string stateName;
    string nextState;
public:
    State();
    virtual ~State();
    State(const State& s);
    State& operator =(const State& s);
    void setStateName(const string& name);
    string getStateName() const;
    virtual void transition(GameEngine* gameEngine, string command) = 0;
    friend ostream& operator <<(ostream& stream, const State& s);
};


//
//STARTUP STATE CLASS
//
class startupState: public State{
public:
    startupState();
    virtual ~startupState();
    startupState(const startupState& aState);
    vector<string> getValidCommand();
    void transition(GameEngine* gameEngine, string command);
    friend ostream& operator <<(ostream& stream, const startupState& s);
private:
    int step;
};


//
//REINFORCEMENT STATE CLASS
//
class reinforcementState: public State{
public:
    reinforcementState();
    virtual ~reinforcementState();
    void transition(GameEngine* gameEngine, string command) override;
private:
    string validCommand;
};


//
//ISSUE ORDERS STATE CLASS
//
class issueOrdersState: public State{
public:
    issueOrdersState();
    virtual ~issueOrdersState();
    void transition(GameEngine* gameEngine, string command) override;
private:
    string validCommand1;
    string validCommand2;
};


//
//EXECUTE ORDERS STATE CLASS
//
class executeOrdersState: public State{
public:

    executeOrdersState();
    virtual ~executeOrdersState();
    void transition(GameEngine* gameEngine, string command) override;
private:
    string validCommand1;
    string validCommand2;
    string validCommand3;
};


//
//END STATE CLASS
//
class endState: public State{
public:
    endState();
    virtual ~endState();
    void transition(GameEngine* gameEngine, string command) override;
private:
    string validCommand1;
    string validCommand2;
};