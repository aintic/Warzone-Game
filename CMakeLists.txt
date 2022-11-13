cmake_minimum_required(VERSION 3.23)
project(COMP_345_START)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cards)
include_directories(CommandProcessing)
include_directories(GameEngine)
include_directories(LoggingObserver)
include_directories(Map)
include_directories(Orders)
include_directories(Player)

add_executable(COMP_345_START
        Cards/Cards.cpp
        Cards/Cards.h
        Cards/CardsDriver.cpp
        Cards/CardsDriver.h
        CommandProcessing/CommandProcessing.cpp
        CommandProcessing/CommandProcessing.h
        CommandProcessing/CommandProcessingDriver.cpp
        CommandProcessing/CommandProcessingDriver.h
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngineDriver.cpp
        GameEngine/GameEngineDriver.h
        LoggingObserver/LoggingObserver.cpp
        LoggingObserver/LoggingObserver.h
        LoggingObserver/LoggingObserverDriver.cpp
        LoggingObserver/LoggingObserverDriver.h
        Map/Map.cpp
        Map/Map.h
        Map/MapDriver.cpp
        Map/MapDriver.h
        Orders/Orders.cpp
        Orders/Orders.h
        Orders/OrdersDriver.cpp
        Orders/OrdersDriver.h
        Player/Player.cpp
        Player/Player.h
        Player/PlayerDriver.cpp
        Player/PlayerDriver.h
        MainDriver.cpp)
