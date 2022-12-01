#include "GameEngine.h"
#include "../Cards/Cards.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


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
    deck = new Deck();
    currentState = new startupState();
    map = nullptr;
    commandProcessor = nullptr;
}

GameEngine::GameEngine(Observer* _obs) {
    deck = new Deck();
    commandProcessor = new CommandProcessor(_obs);
    command = new Command(_obs);
    currentState = new startupState();
    map = nullptr;
    _observers = _obs;
    this->Attach(_obs);
}



GameEngine::GameEngine(int numPlayers) {
    deck = new Deck();
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
    this->Detach();
    for (int i = 0; i < players.size(); i++){
        delete players[i];
    }
    delete deck;
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
    if (this != &g) { //check for self-assignment
        State *otherState = g.currentState->clone(); //create new state
        delete currentState; //delete old one
        currentState = otherState; //set to new state
    }
    return *this;
}

//getter for currentState of the game
State *GameEngine::getCurrentState() {
    return currentState;
}

//setter for currentState of the game
void GameEngine::setCurrentState(State *state) {
    currentState = state;
}

// getter for list of players
vector<Player*> GameEngine::getPlayers() {
    return players;
}

void GameEngine::setPlayers(Player *p) {
    players.push_back(p);
}

// game deck getter
Deck* GameEngine::getDeck() {
    return deck;
}

//method to move to next state. Taking care of memory leak.
void GameEngine::nextState(State *nextState) {
    delete this->currentState;
    this->setCurrentState(nextState);
    Notify(this);

}

void GameEngine::startupPhase(CommandProcessor* c) {

    this->commandProcessor = c;
    bool quit_game = false;

    Command *command;

    do { // loop while not in assign reinforcement phase or until eof reached from command file
        bool go_to_next_state = true;

        command = this->commandProcessor->getCommand(this);

        if(command == nullptr){
            cout << "Invalid command file was provided. Aborting game." << endl;
            return;
        }

        // since get_command takes care of verifying the validity of the command in the given state of the game
        // we can use is statements to execute the command and save the appropriate effect
        string typed_command = command->get_typed_command();

        // for commands like loadmap and add player, the valid command is only the first token of the command
        // for example loadmap examplemap --> valid token is loadmap
        string delimiter = " ";
        string token_command = typed_command.substr(0, typed_command.find(delimiter));

        // MAP LOADING
        if(token_command == "loadmap"){

            string map_string = typed_command.substr(token_command.length() + delimiter.length());
            cout << "\n<<Loading the map "<< map_string << ">>" << endl;

            // delete previous map if any
            delete this->map;
            this->map = nullptr;

            // load the new map
            string map_path = "Maps/" + map_string + ".map";
            this->map = MapLoader::loadMap(map_path);

            if(this->map == nullptr){
                string effect = "Could not load the map <" +map_string + ">";
                command->saveEffect(effect);
                go_to_next_state = false;
            }
            else{
                string effect = "Loaded map <" +map_string + ">";
                command->saveEffect(effect);
            }
        }
        // MAP VALIDATING
        else if(typed_command == "validatemap"){
            cout << "\n<< validating the map>>"<< endl;

            //validate the map
            this->map->validate();

            if(this->map->get_valid()) {
                command->saveEffect("map validated");

                cout<< "Number of continents: " << this->map->get_continents().size() << endl;
                cout<< "Number of territories: " << this->map->get_territories().size() << endl;


            }
            else{
                go_to_next_state = false;
                command->saveEffect("map not valid");
            }

        }

        // ADDING PLAYERS
        else if(token_command == "addplayer"){

            string player_name = typed_command.substr(token_command.length() + delimiter.length());
            int number_of_players = this->getPlayers().size();

            // check if max number of players is reached
            if(number_of_players >=6){
                string message = "Cannot add more players to the game.";
                cout << message <<endl;
                cout << "Please use the command <gamestart>." << endl;
                go_to_next_state = false;
                command->saveEffect(message);
            }
            else{
                cout << "\n<<Adding the player "<< player_name << ">>" << endl;

                // Add the player

                this->players.push_back(new Player(player_name, this));

                string effect = "Added player <" + player_name + ">";
                command->saveEffect(effect);
            }
            number_of_players = this->players.size();
            cout << "Current number of players: " << number_of_players << endl;
        }

        // STARTING THE GAME
        else if (typed_command == "gamestart") {

            // not enough players
            if(this->getPlayers().size() < 2){
                int number_of_players = this->getPlayers().size();
                string message = "Not enough players to start the game.";
                cout << message << " Current number of players is " << number_of_players << "." <<endl;
                cout << "To start the game, please make sure to add 2 to 6 players. " << endl;
                go_to_next_state = false;
                command->saveEffect(message);
            }
            else{
                cout << "\n<<Starting the game>>\n" << endl;

                // start the game

                cout << "a) fairly distributing all the territories to the players: " << endl;

                int counter = 0;
                ::map<int, Territory *> territories = this->map->get_territories();

                // Assign each territory to a player in a round-robin fashion as to ensure that
                // no player should have more than one territory more than any other player.
                for(pair<int,Territory*> territory : territories){
                    int player_index = counter % this->players.size();
                    this->players[player_index]->addTerritory(territory.second);
                    counter++;
                }

                for(Player *player : this->players){
                    cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
                }


                cout << "\nb) determining randomly the order of play of the players in the game: " << endl;

                // shuffle the order of players
                std::random_shuffle(this->players.begin(), this->players.end());

                counter = 1;
                for(Player *player : this->players){
                    cout << counter << ": " << player->getName() << endl;
                    counter++;
                }

                cout << "\nc) giving 50 initial army units to the players, which are placed in their respective reinforcement pool: " << endl;
                for(Player* player : this->players){
                    player->setReinforcementPool(50);
                    cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
                }

                cout << "\nd) players draw 2 initial cards from the deck using the deck’s draw() method: " << endl;
                this->deck = new Deck;

                cout<< *(this->deck) << endl << endl;

                for(Player* player : this->players){
                    this->deck->draw(*player);
                    this->deck->draw(*player);

                    cout << player->getName() << "'s hand: " << *player->getHand() << endl;
                }

                cout << "\ne) switching the game to the play phase: " << endl;


                command->saveEffect("a) fairly distributing all the territories to the players"
                                    "\n\t\t\t b) determining randomly the order of play of the players in the game"
                                    "\n\t\t\t c) giving 50 initial army units to the players, placed in their respective reinforcement pool"
                                    "\n\t\t\t d) players draw 2 initial cards from the deck using the deck's draw() method"
                                    "\n\t\t\t e) switch the game to the play phase");
            }
        }
        // REPLAY OR QUIT
        else if(token_command == "replay"){

            for(Player* player: players){
                delete player;
                player = nullptr;
            }
            delete map;
            map = nullptr;

            delete deck;
            deck = new Deck();

            cout << "Replaying game." << endl;
        }else if(token_command == "quit"){

            cout << "quitting the game" << endl;
            command->saveEffect("Quitting the game. Bye-bye cuties... ;)");
            quit_game = true;
        }

        // NEVER REACH THIS POINT
        else {
            cout << "Something went wrong, please try again...";
            command->saveEffect("Something went wrong");
            go_to_next_state = false;

        }
        if(go_to_next_state){
            this->getCurrentState()->transition(this, token_command);
        }
        else{
            cout << "Still in " << currentState->getStateName() << " state." << endl;
        }

        if(this->getCurrentState()->getStateName() == "Assign reinforcement"){
            mainGameLoop();
        }
    }while(!quit_game);
}

void GameEngine::reinforcementPhase() {
    for (Player *p: players) {
            cout << "num territories: " << p->getNumTerritories() << endl;
            int armyUnits = floor(p->getNumTerritories() / 3);
            cout << "army units : " << armyUnits << endl;
            int continentBonus = map->allContinentsBonus(p);
            cout << "continent bonus : " << continentBonus << endl;
            int reinforcementPool = max(armyUnits + map->allContinentsBonus(p), 3) + p->getReinforcementPool();
            p->setReinforcementPool(reinforcementPool);
            cout << "Player: " << p->getName() << " got " << p->getReinforcementPool() <<
                 " armies during the reinforcement phase!\n" << endl;
    }
    this->nextState(new issueOrdersState());
}

bool GameEngine::executeOrdersPhase() {

    // bool variables to exit the do-while loops when orders done
    bool deployOrdersDone;
    bool allOrdersDone;
    do {
        deployOrdersDone = true;
        for (Player *p: players) {
                cout << "\nChecking deploy of player " << p->getName() << endl;
                if (!p->getPlayerOrderList()->getOrderList().empty()) { //checks that order list isn't empty
                    if (p->getPlayerOrderList()->getTopOrder()->getOrderType() == "Deploy") {
                        p->getPlayerOrderList()->executeOrder(); //executes deploy order
                        deployOrdersDone = false;
                    }
                    else{
                        cout << "No more deploy orders" << endl;
                    }
                }
        }
    } while (!deployOrdersDone);
    cout << "\nDeploy orders finished\n" << endl;
    do {
        allOrdersDone = true;
        for(int i = 0; i < players.size(); i++){
                if (!players[i]->getPlayerOrderList()->getOrderList().empty()) { //checks that order list isn't empty
                    cout << "\nChecking next order of Player " << players[i]->getPlayerID() << " called " << players[i]->getName() << endl;
                    players[i]->getPlayerOrderList()->executeOrder(); //executes deploy order
                    allOrdersDone = false;
                }
                // checks if player left with no territories
            for(int j = 0; j < players.size(); j++){
                if(players[j]->getNumTerritories() == 0){
                    //delete player that is left with no territories
                    cout << "\nPLAYER ELIMINATED (no territories left) : " << *players[j] << endl;
                    delete players[j];
                }
                if(players.size() == 1){
                    //Only one player standing - transition to endState
                    cout << "\nPlayer " << players[0]->getName() << " won the game!!" << endl;
                    this->nextState(new endState());
                    cout << *this->currentState;
                    return false;
                }
            }
        }
    } while (!allOrdersDone);
    for (Player *p : players) {
        p->resetFriendlyList();
        if (p->getStrategy()->getStrategyName() != "Cheater" && p->getConquerer()) {
            deck->draw(*p);
            cout << "\n" << p->getName() << " wins " << *p->getHand()->getCards().back() << " from conquering a territory this turn!" << endl;
            p->resetConquerer();
        }
    }
    // incrementing gameEngine turn and switching to reinforcement state
    GameEngine::turn++;
    this->nextState(new reinforcementState());
    return true;
}

// Main game loop method that runs until stillPlaying boolean true
// executeOrdersPhase return boolean false if only one player left
void GameEngine::mainGameLoop() {
    bool stillPlaying;
    do{
        reinforcementPhase();
        issueOrderPhase();
        stillPlaying = executeOrdersPhase();
    }while(stillPlaying);
}

// Main game loop method for testing purposes that runs the indicated
// number of turns
void GameEngine::mainGameLoop(int turns) {
    for(int i = 0; i < turns; i++){
        reinforcementPhase();
        issueOrderPhase();
        executeOrdersPhase();
    }
}

//method to issue orders in a round-robin fashion
void GameEngine::issueOrderPhase() {
    cout << "Starting Issuing Orders Phase" << endl;
    int playersDoneIssuingOrders = 0;
    //sets the player issue order members
    for (Player *p : this->players){
            p->setIssuableReinforcementPool(p->getReinforcementPool());
            p->setAdvanceAttackOrdersIssued(0);
            p->setAdvanceDefendOrdersIssued(0);
            p->setIsDoneIssuingOrders(false);
    }
    //resets issued army units on each territory
    for (auto &[id, territory] : map->get_territories()) {
        territory->set_issued_army_units(0);
    }
    //calls issueOrder for each player until no more orders to issue
    while (playersDoneIssuingOrders != players.size()) {
        playersDoneIssuingOrders = 0;
        for (Player *p: players) {
                if (p->getIsDoneIssuingOrders()) {
                    playersDoneIssuingOrders++;
                } else {
                    p->issueOrder();
                }
        }
    }
    //transition to execute order state
    this->nextState(new executeOrdersState());
}

//
//ABSTRACT STATE CLASS
//

//default constructor
State::State() = default;

//trivial destructor for State abstract class
State::~State() = default;

//copy constructor
State::State(const State &s) : stateName(s.stateName) {
}

//setter for stateName
void State::setStateName(const string &name) {
    this->stateName = name;
}

//getter for stateName
string State::getStateName() const {
    return stateName;
}

//assignment operator
State &State::operator=(const State &s) {
    stateName = s.stateName;
    return *this;
}


//Stream insertion operators
ostream &operator<<(ostream &stream, const GameEngine &g) {
    return stream << "Current game state: " << g.currentState->getStateName() << endl;
}

ostream &operator<<(ostream &stream, const State &s) {
    if (s.getStateName() == "End") {
        return stream << "\n<<< Game has reached the '" << s.getStateName() << "' state... Thanks for playing! >>>"
                      << endl;
    }
    return stream << "\n<<< Currently transitioning to: '" << s.getStateName() << "' state >>>" << endl;
}

ostream &operator<<(ostream &stream, const startupState &s) {
    if (s.step == 1) {
        return stream << "\nLoaded another map... Still in '" << s.getStateName() << "' state." << endl;
    } else if (s.step == 3) {
        return stream << "\nLoaded another player... Still in '" << s.getStateName() << "' state." << endl;
    } else if (s.step == 4) {
        return stream << "\nYou have entered an invalid command for the '" << s.getStateName() << "' state..." << endl;
    }
    return stream;
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
    this->step = step;
    switch (step) {
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
startupState::~startupState() = default;

//copy constructor
startupState::startupState(const startupState &aState) : State(aState) {
    step = aState.step;
}

//clone method
State *startupState::clone() {
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
    vector<string> vect = {"loadmap", "validatemap", "addplayer", "gamestart"};
    return vect;
}

string startupState::getWrongCommandError() {//method to get wrong command error message
    string error_string = "Something went wrong...";
    switch (step) {
        case 0:
            error_string = "Invalid command for the 'Start' state...\n";
            break;
        case 1:
            error_string = "Invalid command for the 'Map Loaded' state...\n";
            break;
        case 2:
            error_string = "Invalid command for the 'Map Validated' state...\n";
            break;
        case 3:
            error_string = "Invalid command for the 'Players Added' state...\n";
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
void startupState::transition(GameEngine *gameEngine, string command) {
    switch (step) {
        case 0:
            if (command == getValidCommand()[0]) {
                gameEngine->nextState(new startupState(1));
                cout << *gameEngine->getCurrentState();
                break;
            }
        case 1:
            if (command == getValidCommand()[0]) {
                gameEngine->nextState(new startupState(1));
                cout << dynamic_cast<startupState &>(*gameEngine->getCurrentState());
                break;
            } else if (command == getValidCommand()[1]) {
                gameEngine->nextState(new startupState(2));
                cout << *gameEngine->getCurrentState();
                break;
            }
        case 2:
            if (command == getValidCommand()[2]) {
                gameEngine->nextState(new startupState(3));
                cout << *gameEngine->getCurrentState();
                break;
            }
        case 3:
            if (command == getValidCommand()[2]) {
                gameEngine->nextState(new startupState(3));
                cout << dynamic_cast<startupState &>(*gameEngine->getCurrentState());
                break;
            } else if (command == getValidCommand()[3]) {
                gameEngine->nextState(new reinforcementState());
                cout << *gameEngine->getCurrentState();
                break;
            }
        default:
            int temp = step; //temporary change in step to display that invalid command has been entered
            step = 4;
            cout << dynamic_cast<startupState &>(*gameEngine->getCurrentState());
            step = temp; //change back to current step
    }
}


//
//
//REINFORCEMENT STATE CLASS
//
//

//default constructor
reinforcementState::reinforcementState() {
    setStateName(stateName);
    cout << "\nTurn #" << GameEngine::turn << "\n";
}

//default destructor
reinforcementState::~reinforcementState() = default;

//copy constructor
reinforcementState::reinforcementState(const reinforcementState &aState) : State(aState) {
}

//clone method
State *reinforcementState::clone() {
    return new reinforcementState(*this);
}

//assignment operator
reinforcementState &reinforcementState::operator=(const reinforcementState &s) {
    State::operator=(s);
    return *this;
}

//overridden transition method for state transition
void reinforcementState::transition(GameEngine *gameEngine, string command) {
    if (command == validCommand) {
        //<method to assign reinforcement here>
        gameEngine->nextState(new issueOrdersState());
        cout << *gameEngine->getCurrentState();
    } else cout << dynamic_cast<reinforcementState &>(*gameEngine->getCurrentState());
}

string reinforcementState::getWrongCommandError() {//method to get wrong command error message
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
    if (command == validCommand1) {
        //<method to issue an order here>
        cout << dynamic_cast<issueOrdersState &>(*gameEngine->getCurrentState());
    } else if (command == validCommand2) {
        //<method to end issue orders? or just end issue ordering here>
        gameEngine->nextState(new executeOrdersState());
        cout << *gameEngine->getCurrentState();
    } else cout << "\nYou have entered an invalid command for the 'Issue orders' state...\n";
}

string issueOrdersState::getWrongCommandError() {//method to get wrong command error message
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
    if (command == validCommand1) {
        //<method to execute order here>
        cout << dynamic_cast<executeOrdersState &>(*gameEngine->getCurrentState());
    } else if (command == validCommand2) {
        //<method to end order execution>
        GameEngine::turn++;
        gameEngine->nextState(new reinforcementState());
        cout << *gameEngine->getCurrentState();
    } else if (command == validCommand3) {
        //<method of win state here if needed>
        gameEngine->nextState(new endState());
        cout << *gameEngine->getCurrentState();
    } else cout << "\nYou have entered an invalid command for that state...\n";
}

string executeOrdersState::getWrongCommandError() {//method to get wrong command error message
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
State *endState::clone() {
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

string endState::getWrongCommandError() {//method to get wrong command error message
    return "Invalid command for the 'Win' state...";
}

//overridden transition method for state transition
void endState::transition(GameEngine *gameEngine, string command) {
    if (command == validCommand1) {
        //<method to reset game and play again here>
        gameEngine->getCurrentState()->setStateName("Start");
        cout << dynamic_cast<endState &>(*gameEngine->getCurrentState());
        gameEngine->nextState(new startupState());
    } else if (command == validCommand2) {
        //<method for end game statistics and exit here>
        gameEngine->getCurrentState()->setStateName("End");
        cout << *gameEngine->getCurrentState();
    } else cout << "\nYou have entered an invalid command for the 'Win' state...\n";
}

Observer *GameEngine::getObserver() {
    return _observers;
}

string GameEngine::stringToLog() {
    return "Currently in " + this->getCurrentState()->getStateName() + " state";
}
