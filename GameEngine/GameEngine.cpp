#include "GameEngine.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"
#include <iostream>


// Set constant members
const string reinforcementState::validCommand = "issueorder";
const string reinforcementState::stateName = "Assign reinforcement";
const string issueOrdersState::validCommand1 = "issueorder";
const string issueOrdersState::validCommand2 = "endissueorders";
const string issueOrdersState::stateName = "Issue orders";
const string executeOrdersState::validCommand1 = "execorder";
const string executeOrdersState::validCommand2 = "endexecorders";
const string executeOrdersState::validCommand3 = "win";
const string executeOrdersState::stateName = "Execute orders";
const string endState::validCommand1 = "replay";
const string endState::validCommand2 = "quit";
const string endState::stateName = "Win";


//
//GAME ENGINE CLASS
//

//Initializing static turn variable to 1 for the first turn
int GameEngine::turn = 1;

//default constructor
GameEngine::GameEngine() {
    commandProcessor = new CommandProcessor();
    currentState = new startupState();
    map = nullptr;
}

GameEngine::GameEngine(int numPlayers) {
    deck = new Deck;
    for (int i = 0; i < numPlayers; i++){
        this->players.push_back(new Player);
    }
}

//destructor
GameEngine::~GameEngine() {
    delete currentState;
    currentState = nullptr;
    delete commandProcessor;
    commandProcessor = nullptr;
    delete map;
    map = nullptr;
}

//parametrized constructor
GameEngine::GameEngine(State* state) {
    currentState = state;
}

//copy constructor
GameEngine::GameEngine(const GameEngine &g) {
    currentState = g.currentState->clone(); //using clone method to create a deep copy
}

//assignment operator
GameEngine &GameEngine::operator=(const GameEngine &g) {
    if(this != &g){ //check for self-assignment
        State* otherState = g.currentState->clone(); //create new state
        delete currentState; //delete old one
        currentState = otherState; //set to new state
    }
    return *this;
}

//getter for currentState of the game
State* GameEngine::getCurrentState() {
    return currentState;
}

//setter for currentState of the game
void GameEngine::setCurrentState(State* state){
    currentState = state;
}

//method to move to next state. Taking care of memory leak.
void GameEngine::nextState(State* nextState) {
    delete this->currentState;
    this->setCurrentState(nextState);
}

void GameEngine::startupPhase() {
    do{ // loop while not in assign reinforcement phase
        Command* command = this->commandProcessor->getCommand(this);
        // since get_command takes care of verifying the validity of the command in the given state of the game
        // we can use is statements to execute the command and save the appropriate effect
        string typed_command = command->get_typed_command();

        if(typed_command == "loadmap"){
            cout << "loading the map"<< endl;
            command->saveEffect("map loaded");
        }
        else if(typed_command == "validatemap"){
            cout << "validating the map"<< endl;
            command->saveEffect("map validates");

        }
        else if(typed_command == "addplayer"){
            cout << "Adding player"<< endl;
            command->saveEffect("player added");

        }
        else if(typed_command == "gamestart"){
            cout << "Starting the game"<< endl;
            command->saveEffect("game started");

        }
        else{
            cout << "SOMETHING WENT TERRIBLY WRONG!!!";
            command->saveEffect("SOMETHING WENT WRONG");

        }
        this->getCurrentState()->transition(this, command->get_typed_command());
    }while(this->getCurrentState()->getStateName() != "Assign reinforcement");
}

void GameEngine::reinforcementPhase() {
    for(Player* p : players){
        cout << "num territories: " << p->getNumTerritories() << endl;
        int armyUnits = floor(p->getNumTerritories() / 3);
        cout << "army units : " << armyUnits << endl;
        int continentBonus = map->allContinentsBonus(p);
        cout << "continent bonus : " << continentBonus << endl;
        int reinforcementPool = max(armyUnits + map->allContinentsBonus(p), 3);
        cout << "reinforcement : " << reinforcementPool << endl;
        p->setReinforcementPool(max(armyUnits + map->allContinentsBonus(p), 3));
        cout << "Player: " << p->getPlayerID() << " got " <<  p->getReinforcementPool() <<
        " armies during the reinforcement phase!\n" << endl;
    }
}

void GameEngine::issueOrderPhase() {
    cout << "Starting Issuing Orders Phase" << endl;
    int playersDoneIssuingOrders = 0;

    while (playersDoneIssuingOrders != players.size()) {
        playersDoneIssuingOrders = 0;
        for (Player *p: players) {
            if (!p->issueOrder(this->deck)) {
                playersDoneIssuingOrders++;
            }
        }
    }
}
//
//ABSTRACT STATE CLASS
//

//default constructor
State::State() = default;

//trivial destructor for State abstract class
State::~State() = default;

//copy constructor
State::State(const State& s) : stateName(s.stateName){
}

//setter for stateName
void State::setStateName(const string& name) {
    this->stateName = name;
}

//getter for stateName
string State::getStateName() const {
    return stateName;
}

//assignment operator
State& State::operator=(const State &s) {
    stateName = s.stateName;
    return *this;
}



//Stream insertion operators
ostream &operator<<(ostream &stream, const GameEngine &g) {
    return stream << "Current game state: " << g.currentState->getStateName() << endl;
}

ostream& operator<<(ostream& stream, const State& s){
    if(s.getStateName() == "End"){
        return stream << "\n<<< Game has reached the '" << s.getStateName() << "' state... Thanks for playing! >>>" << endl;
    }
    return stream << "\n<<< Currently transitioning to: '" << s.getStateName() << "' state >>>" << endl;
}

ostream& operator<<(ostream& stream, const startupState& s){
    if(s.step == 1){
        return stream << "\nLoading another map... Still in '" << s.getStateName() << "' state." << endl;
    }
    else if(s.step == 3){
        return stream << "\nLoading another player... Still in '" << s.getStateName() <<"' state." << endl;
    }
    else if(s.step == 4){
        return stream << "\nYou have entered an invalid command for the '" << s.getStateName() << "' state..." << endl;
    }
    return  stream;
}

ostream &operator<<(ostream &stream, const reinforcementState &s) {
    return stream << "\nYou have entered an invalid command for the '" << s.getStateName() << "' state..." << endl;
}

ostream &operator<<(ostream &stream, const issueOrdersState &s) {
    return stream << "\nIssuing order... Still in '" << s.getStateName() << "' state." << endl;
}

ostream &operator<<(ostream &stream, const executeOrdersState &s) {
    return stream << "\nExecuting order... Still in '" << s.getStateName() << "' state." << endl;
}

ostream &operator<<(ostream &stream, const endState &s) {
    return stream << "\nStarting another game... Moving back to '" << s.getStateName() << "' state" << endl;
}


//
//
//STARTUP STATE CLASS
//
//

//default constructor
startupState::startupState() {
    step = 0;//by default start at step 0
    setStateName("Start"); //by default start at 'Start'
}

//parametrized constructor for testing purposes
startupState::startupState(int step) {
    step = step;
    switch(step){
        case 0:
            setStateName("Start");
            break;
        case 1:
            setStateName("Map loaded");
            break;
        case 2:
            setStateName("Map validated");
            break;
        case 3:
            setStateName("Players added");
            break;
    }
}

//destructor
startupState::~startupState()= default;

//copy constructor
startupState::startupState(const startupState &aState) : State(aState){
    step = aState.step;
}

//clone method
State *startupState::clone(){
    return new startupState(*this);
}

//assignment operator
startupState &startupState::operator=(const startupState &s) {
    State::operator=(s);
    step = s.step;
    return *this;
}

//method that holds all valid commands
vector<string> startupState::getValidCommand() {
    vector<string> vect = {"loadmap","validatemap","addplayer","gamestart"};
    return vect;
}

string startupState::getWrongCommandError(){//method to get wrong command error message
    string error_string = "Something went wrong...";
    switch (step) {
        case 0:
            error_string = "Invalid command for the 'Start' state...";
            break;
        case 1:
            error_string = "Invalid command for the 'Map Loaded' state...";
            break;
        case 2:
            error_string = "Invalid command for the 'Map Validated' state...";
            break;
        case 3:
            error_string = "Invalid command for the 'Players Added' state...";
            break;
    }
    return error_string;
}


vector<string> startupState::getSpecificValidCommands() { //method to get valid command given the specific state

    vector<string> valid_commands;

    switch (step) {
        case 0:
            valid_commands.push_back(getValidCommand()[0]);
            break;
        case 1:
            valid_commands.push_back(getValidCommand()[0]);
            valid_commands.push_back(getValidCommand()[1]);
            break;
        case 2:
            valid_commands.push_back(getValidCommand()[2]);
            break;
        case 3:
            valid_commands.push_back(getValidCommand()[2]);
            valid_commands.push_back(getValidCommand()[3]);
            break;
    }

    return valid_commands;
}

//method to get current step of startup phase
int startupState::getStateStep() const {
    return this->step;
}

//overridden transition method for state transition
void startupState::transition(GameEngine* gameEngine, string command) {
    switch (step) {
        case 0:
            if (command == getValidCommand()[0]) {
                gameEngine->getCurrentState()->setStateName("Map loaded");
                cout << *gameEngine->getCurrentState(); //currently transitioning
                //<method to load map here>
                step = 1;
                break;
            }
        case 1:
            if(command == getValidCommand()[0]){
                //<method to load map once again here>
                cout << dynamic_cast<startupState&>(*gameEngine->getCurrentState());
                break;
            }
            else if(command == getValidCommand()[1]){
                gameEngine->getCurrentState()->setStateName("Map validated");
                cout << *gameEngine->getCurrentState();
                //<method to validate map here>
                step = 2;
                break;
            }
        case 2:
            if(command == getValidCommand()[2]){
                gameEngine->getCurrentState()->setStateName("Players added");
                cout << *gameEngine->getCurrentState();
                //<method to add player here>
                step = 3;
                break;
            }
        case 3:
            if(command == getValidCommand()[2]){
                //<method to add player again here>
                cout << dynamic_cast<startupState&>(*gameEngine->getCurrentState());
                break;
            }
            else if(command == getValidCommand()[3]){
                //<method to assign countries here>
                gameEngine->nextState(new reinforcementState());
                cout << *gameEngine->getCurrentState();
                break;
            }
        default:
            int temp = step; //temporary change in step to display that invalid command has been entered
            step = 4;
            cout << dynamic_cast<startupState&>(*gameEngine->getCurrentState());
            step = temp; //change back to current step
    }
}


//
//
//REINFORCEMENT STATE CLASS
//
//

//default constructor
reinforcementState::reinforcementState(){
    setStateName(stateName);
    cout << "\nTurn #" << GameEngine::turn << "\n";
}

//default destructor
reinforcementState::~reinforcementState() = default;

//copy constructor
reinforcementState::reinforcementState(const reinforcementState &aState) : State(aState){
}

//clone method
State* reinforcementState::clone() {
    return new reinforcementState(*this);
}

//assignment operator
reinforcementState &reinforcementState::operator=(const reinforcementState &s) {
    State::operator=(s);
    return *this;
}

//overridden transition method for state transition
void reinforcementState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand){
        //<method to assign reinforcement here>
        gameEngine->nextState(new issueOrdersState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << dynamic_cast<reinforcementState&>(*gameEngine->getCurrentState());
}

string reinforcementState::getWrongCommandError(){//method to get wrong command error message
    return "Invalid command for the 'Reinforcement' state...";
}

vector<string> reinforcementState::getSpecificValidCommands() { //method to get valid command given the specific state

    vector<string> valid_commands;

    valid_commands.push_back(validCommand);

    return valid_commands;
}


//
//
//ISSUE ORDERS STATE CLASS
//
//

//default constructor
issueOrdersState::issueOrdersState() {
    setStateName(stateName);
}

//destructor
issueOrdersState::~issueOrdersState() = default;

//copy constructor
issueOrdersState::issueOrdersState(const issueOrdersState &aState) : State(aState) {
}

//clone method
State *issueOrdersState::clone() {
    return new issueOrdersState(*this);
}

//assignment operator
issueOrdersState &issueOrdersState::operator=(const issueOrdersState &s) {
    State::operator=(s);
    return *this;
}

//overridden transition method for state transition
void issueOrdersState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //<method to issue an order here>
        cout << dynamic_cast<issueOrdersState&>(*gameEngine->getCurrentState());
    }
    else if(command == validCommand2){
        //<method to end issue orders? or just end issue ordering here>
        gameEngine->nextState(new executeOrdersState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << "\nYou have entered an invalid command for the 'Issue orders' state...\n";
}

string issueOrdersState::getWrongCommandError(){//method to get wrong command error message
    return "Invalid command for the 'Issue Order' state...";
}

vector<string> issueOrdersState::getSpecificValidCommands() { //method to get valid command given the specific state

    vector<string> valid_commands;

    valid_commands.push_back(validCommand1);
    valid_commands.push_back(validCommand2);

    return valid_commands;
}




//
//
//EXECUTE ORDERS STATE CLASS
//
//

//default constructor
executeOrdersState::executeOrdersState() {
    setStateName(stateName);
}

//destructor
executeOrdersState::~executeOrdersState() = default;

//copy constructor
executeOrdersState::executeOrdersState(const executeOrdersState &aState) : State(aState) {
}

//clone method
State *executeOrdersState::clone() {
    return new executeOrdersState(*this);
}

//assignment operator
executeOrdersState &executeOrdersState::operator=(const executeOrdersState &s) {
    State::operator=(s);
    return *this;
}

//overridden transition method for state transition
void executeOrdersState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //<method to execute order here>
        cout << dynamic_cast<executeOrdersState&>(*gameEngine->getCurrentState());
    }
    else if(command == validCommand2){
        //<method to end order execution>
        GameEngine::turn++;
        gameEngine->nextState(new reinforcementState());
        cout << *gameEngine->getCurrentState();
    }
    else if(command == validCommand3){
        //<method of win state here if needed>
        gameEngine->nextState(new endState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << "\nYou have entered an invalid command for that state...\n";
}

string executeOrdersState::getWrongCommandError(){//method to get wrong command error message
    return "Invalid command for the 'Execute Order' state...";
}

vector<string> executeOrdersState::getSpecificValidCommands() { //method to get valid command given the specific state

    vector<string> valid_commands;

    valid_commands.push_back(validCommand1);
    valid_commands.push_back(validCommand2);
    valid_commands.push_back(validCommand3);

    return valid_commands;
}


//
//
//END STATE CLASS
//
//

//default constructor
endState::endState() {
    setStateName(stateName);
}

//destructor
endState::~endState() = default;

//copy constructor
endState::endState(const endState &aState) : State(aState) {
}

//clone method
State *endState::clone(){
    return new endState(*this);
}

//assignment operator
endState &endState::operator=(const endState &s) {
    State::operator=(s);
    return *this;
}

vector<string> endState::getSpecificValidCommands() { //method to get valid command given the specific state

    vector<string> valid_commands;

    valid_commands.push_back(validCommand1);
    valid_commands.push_back(validCommand2);

    return valid_commands;
}

string endState::getWrongCommandError(){//method to get wrong command error message
    return "Invalid command for the 'Win' state...";
}

//overridden transition method for state transition
void endState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //<method to reset game and play again here>
        gameEngine->getCurrentState()->setStateName("Start");
        cout << dynamic_cast<endState&>(*gameEngine->getCurrentState());
        gameEngine->nextState(new startupState());
    }
    else if(command == validCommand2){
        //<method for end game statistics and exit here>
        gameEngine->getCurrentState()->setStateName("End");
        cout << *gameEngine->getCurrentState();
        delete gameEngine;
        exit(0);
    }
    else cout << "\nYou have entered an invalid command for the 'Win' state...\n";
}