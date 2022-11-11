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

    game->startupPhase();



    //TODO:
    //hey mike just a heads up, (from today's lecture),
    // check out point 1.3.4 and 1.3.5 of the grading sheet.
    // it seems like readCommand and saveCommand must be protected.
    // 🙂 he said he put some hints in the grading sheet so we kinda
    // have a structure to follow

    // win phase will be implemented after the main game loop is done


//    (1) commands can be read from the console using the CommandProcessor class

//    (2) commands can be read from a saved text file using the FileCommandProcessorAdapter

//    (3) commands that are invalid in the current game state are rejected, and valid commands
//    result in the correct effect and state change. This driver function must be in the
//    CommandProcessingDriver.cpp file.

}


//int main(){
//    testCommandProcessor();
//}