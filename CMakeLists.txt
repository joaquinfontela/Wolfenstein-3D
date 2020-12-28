
cmake_minimum_required(VERSION 3.5)
project(Wolfenstein3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g")

set(SOURCE_FILES_SERVER
        common/includes/Thread/Thread.h
        server/includes/Match/Match.h
        server/includes/Match/MatchList.h
        server/includes/Server/ClientAccepter.h
        server/includes/Server/ClientCommunication.h
        server/includes/Server/ConnectionHandler.h
        server/includes/Server/Server.h
        server/includes/Match/Engine.h
        server/includes/Model/Player/Player.h
        server/includes/Model/Game/Game.h
        server/includes/Model/Item/ItemDrop/ItemDrop.h
        server/includes/Model/Item/Item.h
        server/includes/Model/Item/Ammo.h
        server/includes/Model/Item/Blood.h
        server/includes/Model/Item/Chest.h
        server/includes/Model/Item/Cross.h
        server/includes/Model/Item/Crown.h
        server/includes/Model/Item/Cup.h
        server/includes/Model/Item/MedKit.h
        server/includes/Model/Item/Food.h
        server/includes/Model/Item/Key.h
        server/includes/Model/Item/Weapon/Weapon.h
        common/includes/Socket/SocketCommunication.h
        common/includes/Socket/SocketException.h
        common/includes/Socket/SocketListener.h
        common/includes/protocol.h
        server/includes/Control/Command/Command.h
        server/includes/Control/Command/PlayerMove.h
        server/includes/Control/Command/PlayerDisconnected.h
        server/includes/Control/Notification/Notification.h
        server/includes/Control/Notification/PlayerConnected.h
        server/includes/Control/Notification/PlayerUpdatePosition.h
        server/includes/Control/Notification/PlayerDisconnect.h




        common/src/Socket/SocketCommunication.cpp
        common/src/Socket/SocketListener.cpp
        common/src/Socket/SocketWrapper.cpp
        common/src/Thread/Thread.cpp
        server/src/Server/Server.cpp
        server/src/Server/ClientAccepter.cpp
        server/src/Server/ClientCommunication.cpp
        server/src/Server/ConnectionHandler.cpp
        server/src/Match/MatchList.cpp
        server/src/Match/Match.cpp
        server/src/Match/Engine.cpp
        server/src/Model/Player/Player.cpp
        server/src/Model/Game/Game.cpp
        server/src/Model/Item/ItemDrop/ItemDrop.cpp
        server/src/Model/Item/Item.cpp
        server/src/Model/Item/Ammo.cpp
        server/src/Model/Item/Blood.cpp
        server/src/Model/Item/Chest.cpp
        server/src/Model/Item/Cross.cpp
        server/src/Model/Item/Crown.cpp
        server/src/Model/Item/Cup.cpp
        server/src/Model/Item/Food.cpp
        server/src/Model/Item/Key.cpp
        server/src/Model/Item/MedKit.cpp
        server/src/Model/Item/Weapon/Weapon.cpp
        server/src/Control/Command/PlayerMove.cpp
        server/src/Control/Command/PlayerDisconnected.cpp
        server/src/Control/Notification/PlayerConnected.cpp
        server/src/Control/Notification/PlayerUpdatePosition.cpp
        server/src/Control/Notification/PlayerDisconnect.cpp
        server/src/Control/Notification/PlayerPackageUpdate.cpp
        server/src/Control/Command/PlayerADown.cpp
        server/src/Control/Command/PlayerSDown.cpp
        server/src/Control/Command/PlayerDDown.cpp
        server/src/Control/Command/PlayerWDown.cpp

        test/CPPUnit.h
        test/CPPUnit.cpp
        )


add_executable(WolfensteinTest ${SOURCE_FILES_SERVER} test/test.cpp)
add_executable(ServerMain ${SOURCE_FILES_SERVER} serverMain.cpp)
