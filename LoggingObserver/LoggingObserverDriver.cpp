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


    game->startupPhase();


    //OrdersList* ol = new OrdersList;

    Order* testDeploy = new Deploy(game);

    testDeploy->execute();

    /*Order* testAdvance = new Advance(game);
    Order* testBomb = new BombCardOrder(game);
    Order* testBlockade = new BlockadeCardOrder(game);
    Order* testAirlift = new AirliftCardOrder(game);
    Order* testNegotiate = new Negotiate(game);
*/
    //Player* p1 = new Player();
    //p1->getPlayerOrderList()->add(testDeploy);



    /*

    ol->add(testDeploy);
    ol->add(testAdvance);
    ol->add(testBomb);
    ol->add(testBlockade);
    ol->add(testAirlift);
    ol->add(testNegotiate);
*/

}
