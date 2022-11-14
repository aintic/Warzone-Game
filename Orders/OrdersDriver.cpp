//
// Created by Alice on 2022-09-26.
//
#include "Orders.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"
#include <iostream>
#include <fstream>
#include <string>

/**
 * Free function to test Order and OrdersList
 */
void testOrdersExecution() {

    // setup game engine, players and some orders
    cout << "\nSETUP GAME ENGINE, PLAYERS & ORDERS ======================" << endl;
    GameEngine *game1 = new GameEngine();
    string valid_map1 = "../Map/Maps/AnnysPiratenwelt.map";
    Map *map = MapLoader::loadMap(valid_map1);
    Player *p1 = new Player("Mario", game1);
    Player *p2 = new Player("Luigi", game1);
    game1->map = map;
    game1->players.push_back(p1);
    game1->players.push_back(p2);
    int counter = 0;
    ::map<int, Territory *> territories = game1->map->get_territories();
    for(pair<int,Territory*> territory : territories){
        int player_index = counter % game1->players.size();
        game1->players[player_index]->addTerritory(territory.second);
        counter++;
    }
    for(Player* player : game1->players){
        player->setReinforcementPool(25);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }
    for(Player *player : game1->players){
        cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
    }
    p1->addOrder(new Deploy (p1->getTerritories()[5], p1, 0, game1));
    p1->addOrder(new Deploy (p2->getTerritories()[5], p1, 5, game1));
    p1->addOrder(new Deploy (p1->getTerritories()[5], p1, 5, game1));
    p1->addOrder(new Deploy (p1->getTerritories()[12], p1, 3, game1));
    p2->addOrder(new Deploy(p2->getTerritories()[20], p2, 4, game1));
    p2->addOrder(new Deploy(p2->getTerritories()[15], p2, 4, game1));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5]->get_neighbours()[3], p1, 2, game1));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5]->get_neighbours()[2], p1, 2, game1));
    p2->addOrder(new Bomb(p1->getTerritories()[12], p2, game1));
    p1->addOrder(new Blockade(p1->getTerritories()[12], p1, game1));
    p2->addOrder(new Blockade(p1->getTerritories()[11], p2, game1));
    p2->addOrder(new Negotiate(p1, p2, game1));
    p2->addOrder(new Bomb(p1->getTerritories()[5], p2, game1));
    p2->addOrder(new Airlift(p1->getTerritories()[20], p2->getTerritories()[1], p2, 1, game1));
    p2->addOrder(new Airlift(p2->getTerritories()[20], p2->getTerritories()[1], p2, 1, game1));

    // demonstrate validation and execution of all kinds of orders that was hard coded above
    cout << "\nTURN 1 : EXECUTE ORDER PHASE ======================================================" << endl;
    cout << "\nDemonstrates:" << endl;
    cout << "\n- Validation and execution of all orders" << endl;
    cout << "\n- Ownership of a territory is transferred to the attacking player if a territory is conquered as a result of an advance order" << endl;
    cout << "\n- One card is given to a player if they conquer at least one territory in a turn (not more than one card per turn)." << endl;
    cout << "\n- Negotiate order prevents attack between the two players involved." << endl;
    cout << "\n- Blockade order transfers ownership to the Neutral player\n" << endl;

    game1->executeOrdersPhase();

    cout << "\nTURN 2 : ISSUE ORDER PHASE ========================================================" << endl;
    cout << "\nDemonstrates:" << endl;
    cout << "\n- The player who conquered a territory last turn gets a card order and issues it in Issue Order Phase\n" << endl;
    game1->issueOrderPhase();

    cout << "\nREGULAR GAMEPLAY ===================================================================" << endl;
    cout << "\nDemonstrates:" << endl;
    cout << "\n- All orders can be issued and executed by the Game Engine.\n" << endl;

    const string CONSOLE_STRING = "-console";
    const string FILE_STRING = "-file";
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

    // cleanup
    delete game1;
    delete game;
    delete _observers;

    cout << "\nEND OF ORDERS DRIVER ============================================\n" << endl;
}