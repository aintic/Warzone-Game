#include <iostream>
#include <fstream>
#include <string>
#include "../GameEngine/GameEngine.h"
#include "../Tournament/TournamentDriver.h"

using std::cout;
using std::cin;
using std::string;

using namespace std;

void testTournament(){
    const string CONSOLE_STRING = "-console";
    const string FILE_STRING = "-file";

    cout << "\nTESTING TOURNAMENT MODE:\n\n";

    bool valid_initial_command = false;
    CommandProcessor * processor;
    string file_name;

    Observer* _observers = new LogObserver();
    GameEngine* game = new GameEngine(_observers);

    while(!valid_initial_command){

        cout << "Please enter (-console) to input commands from the console or (-file <filename>) to let the game read the commands from a file: " << endl;

        string user_input;

        getline(cin, user_input);

        string delimiter = " ";
        string first_word = user_input.substr(0, user_input.find(delimiter));

        if(user_input == CONSOLE_STRING){
            cout << "[[Reading from console]]" << endl;
            processor = new CommandProcessor(_observers);
            valid_initial_command = true;
        }
        else if(first_word == FILE_STRING && user_input.length() > FILE_STRING.length() + delimiter.length()){
            file_name = "../CommandProcessing/Commands/" + user_input.substr(FILE_STRING.length() + delimiter.length()) + ".txt";

            ifstream file;

            file.open(file_name);
            if(file.fail()){
                cout << "File failed to open. please enter a valid file name:" << endl;
            }
            else{
                valid_initial_command = true;
                cout << "[[Reading from file]]" << endl;
                processor = new FileCommandProcessorAdapter(file_name, _observers);
            }
            file.close();
        }
        else{
            cout<< "Invalid command." << endl;
        }
    }


    game->startupPhase(processor);

    //cout<< "\nCommand processor list of saved commands :\n" << *processor<< endl;

    delete game;
}
