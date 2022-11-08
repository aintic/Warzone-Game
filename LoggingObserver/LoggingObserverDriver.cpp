//
// Created by Hongsuk on 11/1/2022.
//

#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"

#include <iostream>


int main(){



    Observer* _observers = new LogObserver();

    GameEngine* game = new GameEngine(_observers);


    //game->startupPhase();

    //game transition part
    State* map_loaded = new startupState(1);
    State* map_validated = new startupState(2);
    State* players_added = new startupState(3);

    game->nextState(map_loaded);
    game->nextState(map_validated);
    game->nextState(players_added);

    Player* p1 = new Player();
    Order* testDeploy = new Deploy(game);

    OrdersList* ol = new OrdersList(game);

    p1->getPlayerOrderList()->add(testDeploy);


/*
    Order* testDeploy = new Deploy(game);


    Order* testAdvance = new Advance(game);
    Order* testBomb = new BombCardOrder(game);
    Order* testBlockade = new BlockadeCardOrder(game);
    Order* testAirlift = new AirliftCardOrder(game);
    Order* testNegotiate = new Negotiate(game);

    testDeploy->execute();
    testAdvance->execute();
    testBomb->execute();
    testBlockade->execute();
    testAirlift->execute();
    testNegotiate->execute();

    OrdersList* ol = new OrdersList(game);

    cout << "\n============= Add orders =============\n" << endl;
    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);
*/




}
