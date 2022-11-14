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


void testLoggingObserver(){

    cout << "testLoggingObserver executed" << endl;

    Observer* _observers = new LogObserver(); //creating _observer
    //Command and CommandProcessor test
    GameEngine* game = new GameEngine(_observers);


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

    //Order and Order list test
    Player* p1 = new Player("Player1", game);
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
    p1->getPlayerOrderList()->add(testBlockade);
    p1->getPlayerOrderList()->add(testAirlift);
    p1->getPlayerOrderList()->add(testNegotiate);


    game->players.push_back(p1);

    string valid_map1 = "../Map/Maps/AnnysPiratenwelt.map";
    Map *map = MapLoader::loadMap(valid_map1);
    Player *p2 = new Player("Player 2", game);
    Player *p3 = new Player("Player 3", game);
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

    Order *d1 = new Deploy (p2->getTerritories()[1], p2, 0, game);
    d1->execute();
    Order *b1 = new Bomb (p1->getTerritories()[0], p2, game);
    b1->execute();

    p2->getPlayerOrderList()->add(d1);
    p2->getPlayerOrderList()->add(b1);

    Order *a3 = new Airlift (p3->getTerritories()[0],p3->getTerritories()[1], p3, 20, game);
    p3->getPlayerOrderList()->add(a3);
    a3->execute();
    Order *b2 = new Blockade(p3->getTerritories()[0], p3, game);
    b2->execute();
    Order *n1 = new Negotiate(p2, p3, game);
    n1->execute();





    //Game engine transition part
    State* map_loaded = new startupState(1);
    State* map_validated = new startupState(2);
    State* players_added = new startupState(3);
    State* assignReinforcement = new reinforcementState();
    State* executeOrder = new executeOrdersState();
    State* issueOrder = new issueOrdersState();
    State* win = new endState();

    game->nextState(map_loaded);
    game->nextState(map_validated);
    game->nextState(players_added);
    game->nextState(assignReinforcement);
    game->nextState(executeOrder);
    game->nextState(issueOrder);
    game->nextState(win);




    //Clear pointers
    delete game; //game contains the processor and the players


    game = nullptr;
    delete _observers;
    _observers = nullptr;

    delete ol;
    ol = nullptr;
    }



















