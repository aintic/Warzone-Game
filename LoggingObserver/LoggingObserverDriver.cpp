//
// Created by Hongsuk on 11/1/2022.
//

#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"

#include <iostream>
#include <fstream>


int main(){



    Observer* _observers = new LogObserver();

    GameEngine* game = new GameEngine(_observers);


    /*
    bool valid_initial_command = false;
    CommandProcessor * processor;
    string file_name = "../CommandProcessing/Commands/part5_text.txt";
    while(!valid_initial_command){
        valid_initial_command = true;

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
    game->startupPhase(processor);

    cout<< "\nCommand processor list of saved commands :\n" << *processor<< endl;

    delete game;

    cout<< "See you next time!" << endl;
    */

    Player* p1 = new Player();

    OrdersList* ol = new OrdersList(game);
    Order* testDeploy = new Deploy(game);
    Order* testAdvance = new Advance(game);
    Order* testBomb = new Bomb(game);
    Order* testBlockade = new Blockade(game);
    Order* testAirlift = new Airlift(game);
    Order* testNegotiate = new Negotiate(game);

    p1->setPlayerOrderList(ol);
    p1->getPlayerOrderList()->add(testDeploy);
    p1->getPlayerOrderList()->add(testBomb);


    string valid_map1 = "../Map/Maps/AnnysPiratenwelt.map";
    Map *map = MapLoader::loadMap(valid_map1);
    Player *p2 = new Player("Player 1");
    Player *p3 = new Player("Player 2");
    game->map = map;
    game->players.push_back(p2);
    game->players.push_back(p3);

    int counter = 0;
    ::map<int, Territory *> territories = game->map->get_territories();

    for(pair<int,Territory*> territory : territories){
        int player_index = counter % game->players.size();
        game->players[player_index]->addTerritory(territory.second);
        counter++;
    }
    for(Player* player : game->players){
        player->setReinforcementPool(50);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }
    for(Player *player : game->players){
        cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
    }

    Order *d1 = new Deploy (game->map->get_territories().begin()->second, p2, 0, game);

    d1->execute();
    Order *b1 = new Bomb (game->map->get_territories().begin()->second, p2, game);

    b1->execute();

    Order *a3 = new Airlift (game->map->get_territories().begin()->second,game->map->get_territories().begin()->second, p3, 20, game);

    a3->execute();

    }





/*
    //game transition part
    State* map_loaded = new startupState(1);
    State* map_validated = new startupState(2);
    State* players_added = new startupState(3);

    game->nextState(map_loaded);
    game->nextState(map_validated);
    game->nextState(players_added);

    //Orderlist part

    Player* p1 = new Player();

    OrdersList* ol = new OrdersList(game);
    Order* testDeploy = new Deploy(game);

    p1->setPlayerOrderList(ol);
    p1->getPlayerOrderList()->add(testDeploy);









}
*/