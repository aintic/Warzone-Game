#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "Cards.h"

void testPlayerStrategies(){

    GameEngine* game = new GameEngine();
    Player *p1 = new Player("player1", game);
    Player *p2 = new Player("player2", game);
    Player *p3 = new Player("player3", game);
    PlayerStrategy *s1 = new BenevolentPlayerStrategy(p3);

    p3->setStrategy(s1);


    //Adding players to game
    game->players.push_back(p1);
    game->players.push_back(p2);
    game->players.push_back(p3);

    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p1);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p2);
    game->getDeck()->draw(*p3);
    game->getDeck()->draw(*p3);
    game->getDeck()->draw(*p3);

    // load the testing map
    string mapName = "testingMap";
    string map_path = "Maps/" + mapName + ".map";
    game->map = MapLoader::loadMap(map_path);

    if (game->map == nullptr) {
        cout << "Could not load the map <" + mapName + ">";
    } else {
        cout << "Loaded map <" + mapName + ">";
    }

    //validate the map
    game->map->validate();
    cout << *game->map << endl;

    //
    //Testing reinforcement phase
    //
    Territory *t1 = game->map->get_territories()[0];
    Territory *t2 = game->map->get_territories()[1];
    Territory *t3 = game->map->get_territories()[2];
    Territory *t4 = game->map->get_territories()[3];
    Territory *t5 = game->map->get_territories()[4];
    Territory *t6 = game->map->get_territories()[5];
    Territory *t7 = game->map->get_territories()[6];
    Territory *t8 = game->map->get_territories()[7];
    Territory *t9 = game->map->get_territories()[8];
    Territory *t10 = game->map->get_territories()[9];
    Territory *t11 = game->map->get_territories()[10];
    Territory *t12 = game->map->get_territories()[11];
    Territory *t13 = game->map->get_territories()[12];
    Territory *t14 = game->map->get_territories()[13];


    //p1 all territories in continent c2 (bonus 5)
    p1->addTerritory(t3);
    p1->addTerritory(t8);

    //# of territories owned divided by 3
    // 9 / 3 = 3
    p2->addTerritory(t1);
    p2->addTerritory(t2);
    p2->addTerritory(t5);
    p2->addTerritory(t7);
    p2->addTerritory(t9);
    p2->addTerritory(t10);
    p2->addTerritory(t11);
    p2->addTerritory(t12);
    p2->addTerritory(t14);

    //minimal number of reinforcement units (only 3 territories)
    p3->addTerritory(t4);
    p3->addTerritory(t6);
    p3->addTerritory(t13);

    p1->setReinforcementPool(10);
    p2->setReinforcementPool(10);
    p3->setReinforcementPool(10);

    cout << "P3 territories before: " << endl;
    for(int i = 0; i < p3->getNumTerritories(); i++){
        cout << *p3->getTerritories()[i];
        cout << "army units: " << p3->getTerritories()[i]->get_army_units() << endl;
    }

    game->issueOrderPhase();
    game->executeOrdersPhase();

    cout << "P3 territories after: " << endl;
    for(int i = 0; i < p3->getNumTerritories(); i++){
        cout << *p3->getTerritories()[i] << endl;
        cout << "army units: " << p3->getTerritories()[i]->get_army_units() << endl;
    }
}