#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "Cards.h"
#include <string>
using std::cout;
using std::endl;

void testPlayerStrategies(){
    GameEngine* game = new GameEngine();
    Player *p1 = new Player("ABC", game);
    Player *p2 = new Player("DEF", game);
    Player *p3 = new Player("GHI", game);
    PlayerStrategy *s1 = new AggressivePlayerStrategy(p1);
    PlayerStrategy *s2 = new AggressivePlayerStrategy(p2);
    PlayerStrategy *s3 = new AggressivePlayerStrategy(p3);

    //Adding players to game
    game->players.push_back(p1);
    game->players.push_back(p2);
    game->players.push_back(p3);

    // load the testing map
    string mapName = "testingMap";
    string map_path = "Maps/" + mapName + ".map";
    game->map = MapLoader::loadMap(map_path);

    if (game->map == nullptr) {
        cout << "Could not load the map <" + mapName + ">";
    } else {
        cout << "Loaded map <" + mapName + ">" << endl;
    }

    int counter = 0;
    ::map<int, Territory *> territories = game->map->get_territories();
    for(pair<int,Territory*> territory : territories){
        int player_index = counter % game->players.size();
        game->players[player_index]->addTerritory(territory.second);
        counter++;
    }
    for(Player* player : game->players){
        player->setReinforcementPool(25);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }
    for(Player *player : game->players){
        cout << *player << ", Number of territories: " << player->getNumTerritories() << endl;
    }

    for (Player *p : game->players) {
        game->getDeck()->draw(*p);
        game->getDeck()->draw(*p);
    }

    cout << *p1->getHand() << endl;
    cout << *p2->getHand() << endl;
    cout << *p3->getHand() << endl;

    for (Player *p : game->players) {
        cout << p->getName() << ": " << *p->getStrategy() << endl;
        for(int i = 0; i < p->getNumTerritories(); i++){
            cout << *p->getTerritories()[i];
            cout << "army units: " << p->getTerritories()[i]->get_army_units() << endl;
        }
    }

    for (int i = 0; i < 4; i++) {
        game->reinforcementPhase();
        game->issueOrderPhase();
        game->executeOrdersPhase();
    }

    for (Player *p : game->players) {
        cout << p->getName() << ": " << *p->getStrategy() << endl;
        for(int i = 0; i < p->getNumTerritories(); i++){
            cout << *p->getTerritories()[i] << endl;
            cout << "army units: " << p->getTerritories()[i]->get_army_units() << endl;
        }
    }
}