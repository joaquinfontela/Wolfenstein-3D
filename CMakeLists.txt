 
cmake_minimum_required(VERSION 3.5)
project(Wolfenstein3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES_SERVER
        common/includes/Thread/Thread.h
        server/includes/Match/Match.h
        server/includes/Match/MatchList.h
        server/includes/Server/ClientAccepter.h
        server/includes/Server/ClientCommunication.h
        server/includes/Server/Server.h
        server/includes/Model/Player/Player.h
        server/includes/Model/Game/Game.h
        server/includes/Model/Item/ItemDrop/ItemDrop.h
        server/includes/Model/Item/Item.h
        server/includes/Model/Item/MedKit.h
        common/includes/Socket/SocketCommunication.h
        common/includes/Socket/SocketException.h
        common/includes/Socket/SocketListener.h
        common/includes/protocol.h

        common/src/Socket/SocketCommunication.cpp
        common/src/Socket/SocketListener.cpp
        common/src/Thread/Thread.cpp
        server/src/Server/Server.cpp
        server/src/Server/ClientAccepter.cpp
        server/src/Server/ClientCommunication.cpp 
        server/src/Match/MatchList.cpp   
        server/src/Match/Match.cpp
        server/src/Model/Player/Player.cpp
        server/src/Model/Game/Game.cpp
        server/src/Model/Item/ItemDrop/ItemDrop.cpp
        server/src/Model/Item/Item.cpp
        server/src/Model/Item/MedKit.cpp
       
        test/CPPUnit.h
        test/CPPUnit.cpp
        )


add_executable(WolfensteinTest ${SOURCE_FILES_SERVER} test/test.cpp)
