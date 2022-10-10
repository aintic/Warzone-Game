#include "Map/Map.h"
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"
#include"Player/Player.h"



using namespace std;

int main()
{
    // Map 
	testLoadMaps();

    // Player
    testPlayers();

    //Orders list
    testOrdersList();

    //Cards
    testCards();

    //GameEngine
    //testGameStates();
}