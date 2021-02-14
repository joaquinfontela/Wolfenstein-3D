
cmake_minimum_required(VERSION 3.5)
project(Wolfenstein3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wunused -Wuninitialized -L/usr/local/lib -I/usr/local/include -std=c++11 -pthread -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lyaml-cpp")

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
        server/includes/Model/Map/MapLoader.h

        server/includes/Model/Item/Ammo.h
        server/includes/Model/Item/Blood.h
        server/includes/Model/Item/Chest.h
        server/includes/Model/Item/Cross.h
        server/includes/Model/Item/Crown.h
        server/includes/Model/Item/Cup.h
        server/includes/Model/Item/Food.h
        server/includes/Model/Item/Item.h
        server/includes/Model/Item/ItemFactory.h
        server/includes/Model/Item/Key.h
        server/includes/Model/Item/Kit.h
        server/includes/Model/Item/Weapon/WeaponFactory.h
        server/includes/Model/Item/Weapon/Knife.h
        server/includes/Model/Item/Weapon/Shootable/Pistol.h
        server/includes/Model/Item/Weapon/Shootable/Minigun.h
        server/includes/Model/Item/Weapon/Shootable/Shootable.h
        server/includes/Model/Item/Weapon/Shootable/MachineGun.h
        server/includes/Model/Item/Weapon/Shootable/RocketLauncher.h

        server/includes/Model/Wall/Wall.h
        server/includes/Model/Wall/WallFactory.h
        server/includes/Model/Wall/GreyStoneWall.h
        server/includes/Model/Wall/WoodenWall.h
        server/includes/Model/Wall/BlueWall.h
        server/includes/Model/Wall/RockWall.h

        server/includes/Model/Door/Door.h
        server/includes/Model/Door/DoorFactory.h
        server/includes/Model/Door/LockableDoor.h
        server/includes/Model/Door/UnlockableDoor.h

        common/includes/YAML/YAMLMapReader.h
        common/includes/YAML/YAMLMapWriter.h
        common/includes/YAML/YAMLConfigReader.h

        common/includes/Socket/SocketCommunication.h
        common/includes/Socket/SocketException.h
        common/includes/Socket/SocketListener.h
        common/includes/Coordinate/Coordinate.h
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
        common/src/Coordinate/Coordinate.cpp
        server/src/Server/Server.cpp
        server/src/Server/ClientAccepter.cpp
        server/src/Server/ClientCommunication.cpp
        server/src/Server/ConnectionHandler.cpp
        server/src/Match/MatchList.cpp
        server/src/Match/Match.cpp
        server/src/Match/Engine.cpp
        server/src/Model/Player/Player.cpp
        server/src/Model/Player/WeaponInventory.cpp
        server/src/Model/Game/Game.cpp
        server/src/Model/Position/Position.cpp

        common/src/YAML/YAMLMapReader.cpp
        common/src/YAML/YAMLConfigReader.cpp

        server/src/Model/Item/Weapon/Weapon.cpp
        server/src/Model/Item/Weapon/Shootable/Pistol.cpp
        server/src/Model/Item/Weapon/Shootable/RocketLauncher.cpp
        server/src/Model/Item/Weapon/Shootable/Minigun.cpp
        server/src/Model/Item/Weapon/Shootable/MachineGun.cpp
        server/src/Model/Item/Weapon/Shootable/Shootable.cpp
        server/src/Model/Item/Weapon/Knife.cpp
        server/src/Model/Item/Weapon/WeaponFactory.cpp
        server/src/Model/Item/Key.cpp
        server/src/Model/Item/Kit.cpp
        server/src/Model/Item/Blood.cpp
        server/src/Model/Item/Ammo.cpp
        server/src/Model/Item/Chest.cpp
        server/src/Model/Item/Cross.cpp
        server/src/Model/Item/Crown.cpp
        server/src/Model/Item/Cup.cpp
        server/src/Model/Item/Food.cpp
        server/src/Model/Item/ItemFactory.cpp

        server/src/Model/Wall/Wall.cpp
        server/src/Model/Wall/WallFactory.cpp

        server/src/Model/Door/DoorFactory.cpp
        server/src/Model/Door/LockableDoor.cpp
        server/src/Model/Door/UnlockableDoor.cpp

        server/src/Control/Command/PlayerMove.cpp
        server/src/Control/Command/PlayerDisconnected.cpp
        server/src/Control/Notification/PlayerConnected.cpp
        server/src/Control/Notification/PlayerUpdatePosition.cpp
        server/src/Control/Notification/ShotsFired.cpp
        server/src/Control/Notification/PlayerDisconnect.cpp
        server/src/Control/Notification/PlayerPackageUpdate.cpp
        server/src/Control/Notification/DoorMoving.cpp
        server/src/Control/Notification/ScoreBoard.cpp
        server/src/Control/Notification/EndMatchNotif.cpp
        server/src/Control/Notification/StartingMatch.cpp
        server/src/Control/Notification/PlayerPickupItem.cpp
        server/src/Control/Notification/PlayerDropItem.cpp
        server/src/Control/Notification/ElementSwitchPosition.cpp
        server/src/Control/Notification/MissileExplotion.cpp
        server/src/Control/Notification/PlayerDied.cpp
        server/src/Control/Command/PlayerADown.cpp
        server/src/Control/Command/PlayerSDown.cpp
        server/src/Control/Command/PlayerDDown.cpp
        server/src/Control/Command/PlayerWDown.cpp
        server/src/Control/Command/PlayerAUp.cpp
        server/src/Control/Command/PlayerSUp.cpp
        server/src/Control/Command/PlayerDUp.cpp
        server/src/Control/Command/PlayerWUp.cpp
        server/src/Control/Command/PlayerShoot.cpp
        server/src/Control/Command/PlayerInteractDoor.cpp
        server/src/Control/Command/PlayerSwitchWeapon.cpp
        server/src/Control/Command/StartGame.cpp

        server/src/Control/UpdatableEvent/ChangeDoorStatus.cpp
        server/src/Control/UpdatableEvent/RocketMissile.cpp
        server/src/Control/UpdatableEvent/EndMatch.cpp
        server/src/Model/Map/Map.cpp
        server/src/Model/Map/MapLoader.cpp
        server/src/Model/Map/Tile/Tile.cpp

        tests/CPPUnit.h
        tests/CPPUnit.cpp
        )

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)
include_directories(${YAMLCPP_INCLUDE_DIRS})

add_executable(ServerMain ${SOURCE_FILES_SERVER} serverMain.cpp)

target_link_libraries(ServerMain ${YAMLCPP_LIBRARIES})
