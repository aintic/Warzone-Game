#include <iostream>
#include <string>
#include "GameEngine.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../CommandProcessing/CommandProcessingDriver.h"

using std::cout;
using std::cin;
using std::string;

// Part 2:
// Tests the startup phase
void testStartupPhase(){
    testCommandProcessor();
}

//testGameStates creates a console-driven interface that allows the user to navigate
//to different states of the game based on user input. Invalid commands are taken into
//account by the transition method, that only allows a state transition with valid commands.

void testGameStates(){
    GameEngine* game;
    game = new GameEngine();
    string command;
    cout << "\nTESTING GAME STATES\n\n";
    cout << *game; //Displays current game state

    //Game loop that exists when the user enters 'end' command
    do{
        cout << "\nPlease enter command to move to the next state:  ";
        cin >> command;
        game->getCurrentState()->transition(game, command);
    }while(true);
}

void testMainGameLoop(){
    GameEngine g(3);

    g.issueOrderPhase();
}


