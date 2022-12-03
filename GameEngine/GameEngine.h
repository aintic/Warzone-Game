#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../Player/Player.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../CommandProcessing/CommandProcessing.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ostream;
using std::endl;

class Player;
class Deck;
class Command;
class CommandProcessor;

//
//GAME ENGINE CLASS
//
//Purpose: The game engine class currently holds a pointer to a State object, which represents the current state
//         of the game. With the currentState object, the game engine is able to transition to valid states from
//         appropriate user input.
//
class GameEngine : public ILoggable, public Subject{

private:
    class State* currentState;
    class Deck* deck;
    CommandProcessor* commandProcessor;
    Command* command;
public:
    GameEngine(); //default constructor
    GameEngine(int numPlayers);
    ~GameEngine(); //destructor
    GameEngine(State* state); //parametrized constructor
    GameEngine(const GameEngine& g); //copy constructor
    GameEngine& operator =(const GameEngine& g); //assignment operator
    State* getCurrentState(); //currentState getter
    vector<Player*> getPlayers();// players list getter
    void setPlayers(Player *p);
    Deck* getDeck(); // game deck getter
    void setCurrentState(State* state); //currentState setter
    void nextState(State* nextState); //method to change state
    static int turn; //count iterations of main game phase
    friend ostream& operator <<(ostream& stream, const GameEngine& g); //stream insertion operator
    vector<Player*> players;
    Map* map;
    void startupPhase(CommandProcessor* c);
    void reinforcementPhase();
    bool executeOrdersPhase();
    void mainGameLoop();
    void mainGameLoop(int turns);
    void issueOrderPhase();


    GameEngine(Observer* _obs);
    string stringToLog();
    Observer* _observers = nullptr;
    Observer* getObserver();

    friend class Orders;
};


//
//ABSTRACT STATE CLASS
//
//Purpose: The abstract state class serves as the Base class for all derived states of the game. By using the
//         concept of polymorphism, the gameEngine object is able to hold a single currentState member of State
//         type, that changes its behaviour based on the dynamic type of the object when calling the transition method.
//
class State{
protected:
    string stateName;
    string nextState;
    const static string issueOrder;
public:
    State(); //default constructor
    virtual ~State(); //destructor
    State(const State& s); //copy constructor
    virtual State* clone() = 0; //virtual clone method to implement
    State& operator =(const State& s); //assignment operator
    void setStateName(const string& name);
    string getStateName() const;
    virtual void transition(GameEngine* gameEngine, string command) = 0; //virtual method to implement
    virtual vector<string> getSpecificValidCommands() = 0; //virtual method to implement
    virtual string getWrongCommandError() = 0; //method to get wrong command error message
    friend ostream& operator <<(ostream& stream, const State& s); //stream insertion operator
};


//
//STARTUP STATE CLASS
//
//Purpose: The 'startup state' class has been designed to hold all 4 states of the startup phase (start,
//         map loaded, map validated and players added). It has been designed this way as the methods
//         in those 4 states shouldn't drastically change as the game becomes more complex and require
//         minimal user interaction. All 4 states are identified by the private step attribute, from
//         step 0 to 3.
//
class startupState: public State{
public:
    startupState(); //default constructor
    startupState(int step);
    ~startupState() override; //destructor
    startupState(const startupState& aState); //copy constructor
    State* clone() override; //clone method
    startupState& operator =(const startupState& otherState); //assignment operator
    static vector<string> getValidCommand(); //method to get valid
    vector<string> getSpecificValidCommands() override; //method to get valid command given the specific state
    string getWrongCommandError() override; //method to get wrong command error message
    int getStateStep() const; //method to get the current state step
    void transition(GameEngine* gameEngine, string command) override; //method to transition to other state
    friend ostream& operator <<(ostream& stream, const startupState& s); //stream insertion operator
private:
    int step;
};


//
//REINFORCEMENT STATE CLASS
//
//Purpose: The 'reinforcement state' class represents the 'assign reinforcement' part of the main phase of the game.
//         This is also where the turn of each iteration of the main phase is displayed.
//
class reinforcementState: public State{
public:
    reinforcementState(); //default constructor
    ~reinforcementState() override; //destructor
    reinforcementState(const reinforcementState& aState); //copy constructor
    State* clone() override; //clone method
    reinforcementState& operator =(const reinforcementState& otherState); //assignment operator
    void transition(GameEngine* gameEngine, string command) override; //method to transition to other state
    vector<string> getSpecificValidCommands() override; //method to get valid command given the specific state
    string getWrongCommandError() override; //method to get wrong command error message
    friend ostream& operator <<(ostream& stream, const reinforcementState& s); //stream insertion operator
private:
    const static string validCommand;
    const static string stateName;
};


//
//ISSUE ORDERS STATE CLASS
//
//Purpose: The 'issue orders' state class represents the 'issue orders' part of the main phase of the game.
//
//
class issueOrdersState: public State{
public:
    issueOrdersState(); //default constructor
    ~issueOrdersState() override; //destructor
    issueOrdersState(const issueOrdersState& aState); //copy constructor
    State* clone() override; //clone method
    issueOrdersState& operator =(const issueOrdersState& otherState); //assignment operator
    void transition(GameEngine* gameEngine, string command) override; //method to transition to other state
    vector<string> getSpecificValidCommands() override; //method to get valid command given the specific state
    string getWrongCommandError() override; //method to get wrong command error message
    friend ostream& operator <<(ostream& stream, const issueOrdersState& s); //stream insertion operator
private:
    const static string validCommand1;
    const static string validCommand2;
    const static string stateName;
};


//
//EXECUTE ORDERS STATE CLASS
//
//Purpose: The 'execute orders' state class represents the 'execute orders' part of the main phase of the game.
//
class executeOrdersState: public State{
public:
    executeOrdersState(); //default constructor
    ~executeOrdersState() override; //destructor
    executeOrdersState(const executeOrdersState& aState); //copy constructor
    State* clone() override; //clone method
    executeOrdersState& operator =(const executeOrdersState& otherState); //assignment operator
    void transition(GameEngine* gameEngine, string command) override; //method to transition to other state
    vector<string> getSpecificValidCommands() override; //method to get valid command given the specific state
    string getWrongCommandError() override; //method to get wrong command error message
    friend ostream& operator <<(ostream& stream, const executeOrdersState& s); //stream insertion operator
private:
    const static string validCommand1;
    const static string validCommand2;
    const static string validCommand3;
    const static string stateName;
};


//
//END STATE CLASS
//
//Purpose: The 'end' state class represents the 'end' part of the game. This is where the user decides
//         to exit the game or to restart another one. Final statistics also appear here.
//
class endState: public State{
public:
    endState(); //default constructor
    ~endState() override; //destructor
    endState(const endState& aState); //copy constructor
    State* clone() override; //clone method
    endState& operator =(const endState& otherState); //assignment operator
    void transition(GameEngine* gameEngine, string command) override; //method to transition to other state
    vector<string> getSpecificValidCommands() override; //method to get valid command given the specific state
    string getWrongCommandError() override; //method to get wrong command error message
    friend ostream& operator <<(ostream& stream, const endState& s); //stream insertion operator
private:
    const static string validCommand1;
    const static string validCommand2;
    const static string stateName;
};