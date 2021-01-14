#include "../../../includes/Model/Game/Game.h"

#include <time.h>

#include <math.h>
#include <functional>
#include <iostream>
#include <string>

#include <functional>
#include <tuple>

#include "../../../includes/Control/Notification/PlayerPackageUpdate.h"
#include "../../../includes/Control/UpdatableEvent/ChangeDoorStatus.h"
#include "../../../includes/Model/Item/ItemFactory.h"
#include "../../../includes/Model/Player/Player.h"

Game::Game(std::string mapFile, std::string configFile)
    : yamlConfigReader(configFile) {
  std::string mapFileName = "./common/src/YAML/map.yaml";
  auto t1 = std::chrono::steady_clock::now();
  MapLoader mapLoader(mapFileName);
  map = mapLoader.loadMap();
  auto t2 = std::chrono::steady_clock::now();
  std::chrono::duration<float, std::milli> diff;
  diff = t2 - t1;
  std::cout << "[GAME] Map loaded, required time: " << ceil(diff.count()) / 1000
            << "s." << std::endl;
}

void Game::addPlayer(int playerID) {
  Player* newPlayer = new Player(this->yamlConfigReader, *map, playerID);

  this->players[playerID] = newPlayer;
}

void Game::forceDoorStatusChange(int x, int y){

  this->map->forceDoorStatusChange(x, y);
}

void Game::playerShoot(int playerID) {
  Player* attacker = this->players[playerID];

  Player* receiver = nullptr;
  int receiverHealth = 0;

  int att = attacker->attack();
  int range = attacker->getRange();

  if ((receiver = map->traceAttackFrom(attacker, range)) != nullptr) {
    ItemFactory factory;

    att = int((att/sqrt(attacker->calculateDistanceTo(receiver)))) % 10;
    receiverHealth = receiver->takeDamage(*map, att);

    if (receiverHealth == 0) {  // Deberia generar un evento de los items dropeados.
  
    }else if(receiverHealth == -1){

    } // Ya no deberia respawnear, deberia generar un evento de muerte.

  }
}

void Game::updatePositions(float timeElapsed) {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    it->second->update(*(this->map), timeElapsed);
  }

  std::list<Updatable*>::iterator updatableIt = this->updatables.begin();
  for(; updatableIt != this->updatables.end(); ++updatableIt){
    (*updatableIt)->update(timeElapsed, (*this));
  }
}

std::tuple<int, int> Game::moveDoor(int playerID) {

  int x, y;
  std::tie(x, y) = this->map->moveDoor(this->players[playerID]);

  if(x >= 0)
    this->updatables.push_back(new ChangeDoorStatus(x, y));

  return std::make_tuple(x, y);

}

void Game::sendUpdateMessages(WaitingQueue<Notification*>& notis) {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    PlayerData data;
    if (it->second->hasToBeUpdated()) {
      it->second->fillPlayerData(data);
      PlayerPackageUpdate* noti = new PlayerPackageUpdate(it->first, data);
      notis.push(noti);
    }
  }

  std::list<Updatable*>::iterator updateIt = this->updatables.begin();
  bool done = false;

  while(updateIt != this->updatables.end()){
    if((done = (*updateIt)->notify(notis))){
      delete (*updateIt);
      updateIt = this->updatables.erase(updateIt);
    }else
      ++updateIt;
  }
}

bool Game::removePlayer(int playerID) {
  std::map<int, Player*>::iterator it = this->players.find(playerID);

  if (it != this->players.end()) {
    this->map->removePlayer(int(it->second->getX()), int(it->second->getY()),
                            it->second);
    delete it->second;
    this->players.erase(it);
    return true;
  }

  return false;
}

void Game::updatePlayerMoveSpeed(int playerID, double moveSpeed) {
  this->players[playerID]->updateMoveSpeed(moveSpeed);
}

void Game::updatePlayerRotationSpeed(int playerID, double rotSpeed) {
  this->players[playerID]->updateRotationSpeed(rotSpeed);
}
void Game::start() {
  // Deberia controlar la logica de iniciar el juego -> mandar la notificacion a
  // los jugadores
}

void Game::end() {
  // Lo mismo pero para terminarlo.
}

Game::~Game() {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    delete it->second;
  }

  delete this->map;
}
