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
 *
 * This function sets up a Game Engine with Players and some hardcoded orders,
 * then runs the IssueOrderPhase and ExecuteOrderPhase,
 * to make sure each order will be executed at least once,
 * and to demonstrate validation of different orders.
 */
void testOrdersExecution() {

    cout << "\nSETUP GAME ENGINE, PLAYERS & ORDERS ======================" << endl;

    GameEngine *game = new GameEngine();
    string valid_map1 = "../Map/Maps/AnnysPiratenwelt.map";
    Map *map = MapLoader::loadMap(valid_map1);
    Player *p1 = new Player("Mario", game);
    Player *p2 = new Player("Luigi", game);
    game->map = map;
    game->players.push_back(p1);
    game->players.push_back(p2);
    Card *bomb = new BombCard();
    Card *blockade = new BlockadeCard();
    Card *airlift = new AirliftCard();
    Card *negotiate = new DiplomacyCard();
    Card *reinforcement = new ReinforcementCard();
    p1->getHand()->addCard(bomb);
    p1->getHand()->addCard(negotiate);
    p2->getHand()->addCard(blockade);
    p2->getHand()->addCard(airlift);
    p2->getHand()->addCard(reinforcement);
    int counter = 0;
    ::map<int, Territory *> territories = game->map->get_territories();
    for(pair<int,Territory*> territory : territories){
        int player_index = counter % game->players.size();
        game->players[player_index]->addTerritory(territory.second);
        counter++;
    }
    for(Player* player : game->players){
        player->setReinforcementPool(8);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }
    for(Player *player : game->players){
        cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
    }
    p1->addOrder(new Deploy (p1->getTerritories()[4], p1, 0, game));
    p1->addOrder(new Deploy (p1->getTerritories()[5], p1, 4, game));
    p1->addOrder(new Deploy (p1->getTerritories()[12], p1, 4, game));
    p2->addOrder(new Deploy(p1->getTerritories()[20], p2, 4, game));
    p2->addOrder(new Deploy(p2->getTerritories()[20], p2, 4, game));
    p2->addOrder(new Bomb(p1->getTerritories()[5], p2, game));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5], p1, 0, game));
    p1->addOrder(new Advance(p1->getTerritories()[5], p1->getTerritories()[5]->get_neighbours()[2], p1, 2, game));
    p1->addOrder(new Advance( p1->getTerritories()[5], p2->getTerritories()[1], p1, 2, game));
    p1->addOrder(new Blockade(p1->getTerritories()[12], p1, game));
    p2->addOrder(new Blockade(p1->getTerritories()[11], p2, game));
    p2->addOrder(new Negotiate(p1, p2, game));
    p2->addOrder(new Bomb(p1->getTerritories()[5], p2, game));
    p2->addOrder(new Airlift(p1->getTerritories()[20], p2->getTerritories()[1], p2, 1, game));
    p2->addOrder(new Airlift(p2->getTerritories()[20], p2->getTerritories()[1], p2, 1, game));

    cout << "\nTURN 1 : ISSUE ORDER PHASE ============================================\n" << endl;
    game->issueOrderPhase();

    cout << "\nTURN 1 : EXECUTE ORDER PHASE ===========================================\n" << endl;
    game->executeOrdersPhase();

    cout << "\nTURN 2 : ISSUE ORDER PHASE ============================================\n" << endl;
    game->issueOrderPhase();
}