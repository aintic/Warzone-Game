#include <iostream>
#include <string>
#include "GameEngine.h"
using std::cout;
using std::cin;
using std::string;


void testGameStates(){

    GameEngine* game;
    game = new GameEngine();
    string command;
    cout << "\nGame begins in state: ";
    cout << game->getCurrentState()->getStateName() << "\n";

    do{
        cout << "\nPlease enter command to move to the next state: \n";
        cin >> command;
        game->getCurrentState()->transition(game, command);
    }while(true);

}



int main()
{
    testGameStates();
}