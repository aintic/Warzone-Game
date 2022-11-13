cmake_minimum_required(VERSION 3.23)
project(COMP_345_A2_Main)

set(CMAKE_CXX_STANDARD 14)

include_directories(../COMP-345-A2-Main/Cards)
include_directories(../COMP-345-A2-Main/CommandProcessing)
include_directories(../COMP-345-A2-Main/GameEngine)
include_directories(../COMP-345-A2-Main/Map)
include_directories(../COMP-345-A2-Main/Orders)
include_directories(../COMP-345-A2-Main/Player)

add_executable(COMP_345_A2_Main
        ../COMP-345-START/Cards/Cards.cpp
        ../COMP-345-START/Cards/Cards.h
        ../COMP-345-START/Cards/CardsDriver.cpp
        ../COMP-345-START/Cards/CardsDriver.h
        ../COMP-345-START/CommandProcessing/CommandProcessing.cpp
        ../COMP-345-START/CommandProcessing/CommandProcessing.h
        ../COMP-345-START/CommandProcessing/CommandProcessingDriver.cpp
        ../COMP-345-START/CommandProcessing/CommandProcessingDriver.h
        ../COMP-345-START/GameEngine/GameEngine.cpp
        ../COMP-345-START/GameEngine/GameEngine.h
        ../COMP-345-START/GameEngine/GameEngineDriver.cpp
        ../COMP-345-START/GameEngine/GameEngineDriver.h
        ../COMP-345-START/Map/Map.cpp
        ../COMP-345-START/Map/Map.h
        ../COMP-345-START/Map/MapDriver.cpp
        ../COMP-345-START/Map/MapDriver.h
        ../COMP-345-START/Orders/Orders.cpp
        ../COMP-345-START/Orders/Orders.h
        ../COMP-345-START/Orders/OrdersDriver.cpp
        ../COMP-345-START/Orders/OrdersDriver.h
        ../COMP-345-START/Player/Player.cpp
        ../COMP-345-START/Player/Player.h
        ../COMP-345-START/Player/PlayerDriver.cpp
        ../COMP-345-START/Player/PlayerDriver.h
        ../COMP-345-START/MainDriver.cpp
        ../COMP-345-START/LoggingObserver/LoggingObserver.cpp
        ../COMP-345-START/LoggingObserver/LoggingObserver.h
        ../COMP-345-START/LoggingObserver/LoggingObserverDriver.cpp
        ../COMP-345-START/LoggingObserver/LoggingObserverDriver.h)
