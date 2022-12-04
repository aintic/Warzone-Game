#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include <string>
using std::cout;
using std::endl;

void testPlayerStrategies() {
    GameEngine *game = new GameEngine();
    Player *p1 = new Player("Alice", game);
    Player *p2 = new Player("Daria", game);
    Player *p3 = new Player("Hongsuk", game);
    Player *p4 = new Player("Michael", game);

    PlayerStrategy *s1 = new AggressivePlayerStrategy(p1);
    PlayerStrategy *s2 = new BenevolentPlayerStrategy(p2);
    PlayerStrategy *s3 = new NeutralPlayerStrategy(p3);
    PlayerStrategy *s4 = new HumanPlayerStrategy(p4);

    //Adding players to game
    game->players.push_back(p1);
    game->players.push_back(p2);
    game->players.push_back(p3);
    game->players.push_back(p4);


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
    for (pair<int, Territory *> territory: territories) {
        int player_index = counter % game->players.size();
        game->players[player_index]->addTerritory(territory.second);
        counter++;
    }

    cout << endl;
    for (Player *player: game->players) {
        player->setReinforcementPool(25);
        cout << player->getName() << "'s reinforcement pool: " << player->getReinforcementPool() << endl;
    }

    cout << endl;
    for (Player *player: game->players) {
        cout << *player << " Number of territories: " << player->getNumTerritories() << endl;
    }

    for (Player *p: game->players) {
        game->getDeck()->draw(*p);
        game->getDeck()->draw(*p);
    }

    cout << endl;
    cout << *p1->getHand() << endl;
    cout << *p2->getHand() << endl;
    cout << *p3->getHand() << endl;
    cout << *p4->getHand() << endl;

    cout << endl;
    for (Player *p: game->players) {
        cout << "\n" << p->getName() << ": " << *p->getStrategy() << endl;
        for (int i = 0; i < p->getNumTerritories(); i++) {
            cout << *p->getTerritories()[i];
            cout << "army units: " << p->getTerritories()[i]->get_army_units() << endl;
        }
    }

    for (int i = 0; i < 1; i++) {
        cout << endl;
        game->reinforcementPhase();
        game->issueOrderPhase();
        game->executeOrdersPhase();
    }

    cout << "Player " << *p4 << " is now a Cheater!" << endl;
    cout << "Player " << *p2 << " is now Aggressive!" << endl;

    PlayerStrategy *s5 = new CheaterPlayerStrategy(p4);
    PlayerStrategy *s6 = new AggressivePlayerStrategy(p2);

    for (int i = 0; i < 2; i++) {
        cout << endl;
        game->reinforcementPhase();
        game->issueOrderPhase();
        game->executeOrdersPhase();
    }

    cout << endl;
    for (Player *p: game->players) {
        cout << "\n" << p->getName() << ": " << *p->getStrategy() << endl;
        for (int i = 0; i < p->getNumTerritories(); i++) {
            cout << *p->getTerritories()[i] << endl;
            cout << "army units: " << p->getTerritories()[i]->get_army_units() << endl;
        }
    }
}