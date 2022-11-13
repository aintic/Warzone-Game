//
// Created by Alice on 2022-09-26.
//
#include "Orders.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"

/**
 * Free function to test Order and OrdersList
 */
void testOrdersExecution() {

    GameEngine *game = new GameEngine();
    string valid_map1 = "../Map/Maps/AnnysPiratenwelt.map";
    Map *map = MapLoader::loadMap(valid_map1);
    Player *p1 = new Player("Player 1", game);
    Player *p2 = new Player("Player 2", game);
    game->map = map;
    game->players.push_back(p1);
    game->players.push_back(p2);

    Card *bomb = new BombCard();
    Card *blockade = new BlockadeCard();
    Card *airlift = new AirliftCard();
    Card *negotiate = new DiplomacyCard();
    p1->getHand()->addCard(bomb);
    p1->getHand()->addCard(negotiate);
    p2->getHand()->addCard(blockade);
    p2->getHand()->addCard(airlift);

    int counter = 0;
    ::map<int, Territory *> territories = game->map->get_territories();

    for(pair<int,Territory*> territory : territories){
        int player_index = counter % game->players.size();
        game->players[player_index]->addTerritory(territory.second);
        counter++;
    }

    for(Player* player : game->players){
        player->setReinforcementPool(5);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }

    for(Player *player : game->players){
        cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
    }

    p1->addOrder(new Deploy (p1->getTerritories()[4], p1, 0, game));
    p1->addOrder(new Deploy (p1->getTerritories()[5], p1, 5, game));
    p2->addOrder(new Deploy(p1->getTerritories()[20], p2, 5, game));
    p2->addOrder(new Deploy(p2->getTerritories()[20], p2, 5, game));
    p2->addOrder(new Bomb(p1->getTerritories()[5], p2, game));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5], p1, 0, game));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5]->get_neighbours()[2], p1, 2, game));
    p1->addOrder(new Advance(p1->getTerritories()[5], p2->getTerritories()[1], p1, 2, game));
    p1->addOrder(new Blockade(p1->getTerritories()[12], p1, game));
    p2->addOrder(new Blockade(p1->getTerritories()[11], p2, game));
    p2->addOrder(new Negotiate(p1, p2, game));
    p2->addOrder(new Bomb(p1->getTerritories()[5], p2, game));
    p2->addOrder(new Airlift(p1->getTerritories()[20], p2->getTerritories()[1], p2, 1, game));
    p2->addOrder(new Airlift(p2->getTerritories()[20], p2->getTerritories()[1], p2, 1, game));

    //game->issueOrderPhase();
    game->executeOrdersPhase();


//    // create new orders' list and one order of each kind
//    OrdersList* ol = new OrdersList;
//    Order* testDeploy = new Deploy;
//    Order* testAdvance = new Advance;
//    Order* testBomb = new Bomb;
//    Order* testBlockade = new Blockade;
//    Order* testAirlift = new Airlift;
//    Order* testNegotiate = new Negotiate;
//
//
//
//    // add orders
//    cout << "\n============= Add orders =============\n" << endl;
//    ol->add(testDeploy);
//    cout << "Order added. Current list: \n" << *ol << endl;
//    ol->add(testAdvance);
//    cout << "Order added. Current list: \n" << *ol << endl;
//    ol->add(testBomb);
//    cout << "Order added. Current list: \n" << *ol << endl;
//    ol->add(testBlockade);
//    cout << "Order added. Current list: \n" << *ol << endl;
//    ol->add(testAirlift);
//    cout << "Order added. Current list: \n" << *ol << endl;
//    ol->add(testNegotiate);
//    cout << "Order added. Current list: \n" << *ol << endl;
//
//    // move orders
//    cout << "\n============= Move orders 1 and 3 =============\n" << endl;
//    ol->move(1, 3);
//    cout << "Orders swapped. Current list: \n" << *ol << endl;
//    cout << "\n============= Move orders 4 and 5 =============\n" << endl;
//    ol->move(4, 5);
//    cout << "Orders swapped. Current list: \n" << *ol << endl;
//
//    // delete orders
//    cout << "\n============= Delete order 3 =============\n" << endl;
//    ol->remove(3);
//    cout << "Order deleted. Current list: \n" << *ol << endl;
//    cout << "\n============= Delete order 2 =============\n" << endl;
//    ol->remove(2);
//    cout << "Order deleted. Current list: \n" << *ol << endl;
//
//    cout << "\n============= Copy list =============\n" << endl;
//    OrdersList *newOl = new OrdersList(*ol);
//    cout << "Copied list: \n" << *newOl << endl;
//    newOl->executeList();
//
//
//    // execute list - invokes validate() and execute() method on each order then delete order in list
//    cout << "\n============= Execute list =============\n" << endl;
//    ol->executeList();
//    cout << "\n=========================================\n" << endl;



    // cleanup
    // delete ol;
    // ol = NULL;
}