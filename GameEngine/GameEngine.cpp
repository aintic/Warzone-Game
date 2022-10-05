#include "GameEngine.h"
#include <iostream>
//#include <string>
//#include <vector>
//using std::cout;
//using std::cin;
//using std::string;
//using std::vector;


//Game loop
//
//GAME ENGINE STATE CLASS
//

//Initializing static variable
int GameEngine::turn = 1;

GameEngine::GameEngine() {
    currentState = new startupState();
}

State* GameEngine::getCurrentState() {
    return currentState;
}

void GameEngine::setCurrentState(State* state){
    currentState = state;
}

void GameEngine::nextState(State* nextState) {
    delete this->currentState;
    this->setCurrentState(nextState);
}


//
//ABSTRACT STATE CLASS
//

//Trivial destructor for State abstract class
State::State() = default;

State::~State() = default;

//Copy constructor
State::State(const State& s) : stateName(s.stateName){
}

void State::setStateName(const string& name) {
    this->stateName = name;
}

string State::getStateName() const {
    return stateName;
}

//is this a deep copy?
State& State::operator=(const State &s) {
    this->stateName = s.stateName;
    return *this;
}



//Stream insertion operators
ostream& operator<<(ostream& stream, const State& s){
    return stream << "Currently transitioning to: '" << s.getStateName() << "' state" << endl;
}

ostream& operator<<(ostream& stream, const startupState& state){
    //if(s.getStateName() == "Map loaded")
    return stream << "Loading another map... Still in '" << state.getStateName() << "' state\n" << endl;
}






//
//STARTUP STATE CLASS
//

//Default constructor
startupState::startupState() {
    step = 0;//by default start at step 0
    setStateName("Start"); //by default start at 'Start'
}

//Destructor
startupState::~startupState() {
}

//Copy constructor
startupState::startupState(const startupState &aState) : State(aState), step(aState.step){
}

vector<string> startupState::getValidCommand() {
    vector<string> vect = {"loadmap","validatemap","addplayer","assigncountries"};
    return vect;
}

void startupState::transition(GameEngine* gameEngine, string command) {

    switch (step) {
        case 0:
            if (command == getValidCommand()[0]) {
                gameEngine->getCurrentState()->setStateName("Map loaded");
                cout << *gameEngine->getCurrentState(); //currently transitioning
                //method to load map
                step = 1;
                break;
            }
        case 1:
            if(command == getValidCommand()[0]){
                //method to load map once again
                cout << dynamic_cast<startupState&>(*gameEngine->getCurrentState());
                cout << "Loading another map... Still in 'Map loaded' state\n";
                break;
            }
            else if(command == getValidCommand()[1]){
                gameEngine->getCurrentState()->setStateName("Map validated");
                cout << *gameEngine->getCurrentState();
                //method to validate map
                step = 2;
                break;
            }
        case 2:
            if(command == getValidCommand()[2]){
                gameEngine->getCurrentState()->setStateName("Players added");
                cout << *gameEngine->getCurrentState();
                //method to add player
                step = 3;
                break;
            }
        case 3:
            if(command == getValidCommand()[2]){
                //method to add player again
                cout << "Loading another player... Still in 'Players added' state\n";
                break;
            }
            else if(command == getValidCommand()[3]){
                //method to assign countries
                gameEngine->nextState(new reinforcementState());
                cout << *gameEngine->getCurrentState();
                break;
            }
        default:
            cout << "You have entered an invalid command for that state...\n";
    }
}



//
//REINFORCEMENT STATE CLASS
//
reinforcementState::reinforcementState(){
    validCommand = "issueorder";
    setStateName("Assign reinforcement");
    cout << "\nTurn #" << GameEngine::turn << "\n";
}

reinforcementState::~reinforcementState() {
    //what should destructor contain?
}

void reinforcementState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand){
        //method to assign reinforcement
        gameEngine->nextState(new issueOrdersState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << "You have entered an invalid command for that state...\n";
}




//
//ISSUE ORDERS STATE CLASS
//
issueOrdersState::issueOrdersState() {
    validCommand1 = "issueorder";
    validCommand2 = "endissueorders";
    setStateName("Issue orders");
}

issueOrdersState::~issueOrdersState() {

}

void issueOrdersState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //method to issue an order
        cout << "Issuing order... Still in 'issue order' state\n";
    }
    else if(command == validCommand2){
        //method to end issue orders? or just end issue ordering
        gameEngine->nextState(new executeOrdersState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << "You have entered an invalid command for that state...\n";
}



//
//EXECUTE ORDERS STATE CLASS
//
executeOrdersState::executeOrdersState() {
    validCommand1 = "execorder";
    validCommand2 = "endexecorders";
    validCommand3 = "win";
    setStateName("Execute order");
}

executeOrdersState::~executeOrdersState() {

}

void executeOrdersState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //method to execute order
        cout << "Executing order... Still in 'execute order' state\n";
    }
    else if(command == validCommand2){
        //method to end order execution
        GameEngine::turn++;
        gameEngine->nextState(new reinforcementState());
        cout << *gameEngine->getCurrentState();
    }
    else if(command == validCommand3){
        //method of win state
        gameEngine->nextState(new endState());
        cout << *gameEngine->getCurrentState();
    }
    else cout << "You have entered an invalid command for that state...\n";
}


//
//END STATE CLASS
//
endState::endState() {
    validCommand1 = "play";
    validCommand2 = "end";
    setStateName("Win");
}

endState::~endState() {

}

void endState::transition(GameEngine *gameEngine, string command) {
    if(command == validCommand1){
        //reset game and play again?
        cout << "Starting another game... Moving back to 'Start state\n";
        gameEngine->nextState(new startupState());
    }
    else if(command == validCommand2){
        //end game statistics and exit
        cout << "Game has reached the 'End' state... Thanks for playing\n";
        gameEngine->getCurrentState()->setStateName("end");
        exit(0);
    }
    else cout << "You have entered an invalid command for that state...\n";
}



















