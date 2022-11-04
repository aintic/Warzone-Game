#include <iostream>
#include <string>
#include "CommandProcessingDriver.h"
#include "../GameEngine/GameEngine.h"
using std::cout;
using std::cin;
using std::string;

using namespace std;

void testCommandProcessor(){
    cout << "\nTESTING COMMAND PROCESSING\n\n";

    GameEngine* game;
    game = new GameEngine();

    CommandProcessor* processor;
    processor = new CommandProcessor();


    cout << *game; //Displays current game state

    //Game loop that exists when the user enters 'end' command
    do{
        game->getCurrentState()->transition(game, processor->getCommand(game));
    }while(true);



//    (1) commands can be read from the console using the CommandProcessor class

//    (2) commands can be read from a saved text file using the FileCommandProcessorAdapter

//    (3) commands that are invalid in the current game state are rejected, and valid commands
//    result in the correct effect and state change. This driver function must be in the
//    CommandProcessingDriver.cpp file.

}



//
//int main(){
//    testCommandProcessor();
//}