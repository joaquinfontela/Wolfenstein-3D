#include "../../../includes/Model/Game/Game.h"

#include <limits.h>
#include <math.h>
#include <time.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>

#include "../../../includes/Control/Notification/EndMatchNotif.h"
#include "../../../includes/Control/Notification/PlayerDropItem.h"
#include "../../../includes/Control/Notification/PlayerPackageUpdate.h"
#include "../../../includes/Control/Notification/StartingMatch.h"

#include "../../../includes/Control/UpdatableEvent/ChangeDoorStatus.h"
#include "../../../includes/Control/UpdatableEvent/EndMatch.h"
#include "../../../includes/Control/UpdatableEvent/RocketMissile.h"
#include "../../../includes/Model/Item/ItemFactory.h"
#include "../../../includes/Model/Player/Player.h"

Game::Game(std::string mapFile, std::string configFile)
    : yamlConfigReader(configFile), yamlMapReader(mapFile) {
  auto t1 = std::chrono::steady_clock::now();
  started = false;

  MapLoader mapLoader(mapFile);
  map = mapLoader.loadMap();
  auto t2 = std::chrono::steady_clock::now();
  std::chrono::duration<float, std::milli> diff;
  diff = t2 - t1;
  std::cout << "[GAME] Map loaded, required time: " << ceil(diff.count()) / 1000
            << "s." << std::endl;
}

void Game::setShooting(int playerID, bool state) {
  this->players[playerID]->setShooting(state);
}

void Game::addPlayer(int playerID, WaitingQueue<Notification*>& notis) {
  Player* newPlayer = new Player(this->yamlConfigReader, *map, playerID);

  this->players[playerID] = newPlayer;

  if (this->players.size() == 1) newPlayer->setAdmin();

  this->sendGameStatus(notis);
}

bool Game::forceDoorStatusChange(int x, int y) {
  return this->map->forceDoorStatusChange(x, y);
}

void Game::playerSwitchWeapon(int playerID, int weaponPos) {
  this->players[playerID]->equipWeapon(weaponPos);
}

void Game::playerShoot(int playerID, WaitingQueue<Notification*>& notis) {}

void Game::generateRadiusDamage(int x, int y,
                                WaitingQueue<Notification*>& notif) {
  int damage = (rand() + 1) % 10;
  this->map->applyDamageOnRadiusFrom(damage, x, y, notif);
}

bool Game::moveRocketMissileFrom(double x, double y, double newX, double newY,
                                 WaitingQueue<Notification*>& notif) {
  if (!map->moveTo(x, y, newX, newY)) {
    this->generateRadiusDamage(int(newX), int(newY), notif);
    return true;
  }

  return false;
}

void Game::update(float timeElapsed, WaitingQueue<Notification*>& notis) {
  if (!started) return;
  this->updatePositions(timeElapsed, notis);
  this->sendUpdateMessages(notis);
}

void Game::updatePositions(float timeElapsed,
                           WaitingQueue<Notification*>& notis) {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if(!it->second->isDead())
      it->second->update(timeElapsed, notis, this->updatables);
  }

  std::list<Updatable*>::iterator updatableIt = this->updatables.begin();
  for (; updatableIt != this->updatables.end(); ++updatableIt) {
    (*updatableIt)->update(timeElapsed, (*this), notis);
  }
}

std::tuple<int, int> Game::moveDoor(int playerID) {
  int x, y;
  std::tie(x, y) = this->map->moveDoor(this->players[playerID]);

  if (x >= 0) {
    this->updatables.push_back(new ChangeDoorStatus(
        x, y, 0.5f, false));  // Hace la puerta atravesable tras 0.5 segundos.
    this->updatables.push_back(new ChangeDoorStatus(
        x, y, 8.0f, true));  // Cierra la puerta tras 8 segundos.
  }

  return std::make_tuple(x, y);
}

void Game::sendGameStatus(WaitingQueue<Notification*>& notis) {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {

    if(!it->second->isDead()){
      PlayerData data;
      it->second->fillPlayerData(data);
      PlayerPackageUpdate* noti = new PlayerPackageUpdate(it->first, data);
      notis.push(noti);
    }

  }
}

void Game::sendUpdateMessages(WaitingQueue<Notification*>& notis) {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    PlayerData data;
    if (it->second->hasToBeUpdated() && !it->second->isDead()) {
      it->second->fillPlayerData(data);
      it->second->setNotifiable(false);
      PlayerPackageUpdate* noti = new PlayerPackageUpdate(it->first, data);
      notis.push(noti);
    }
  }

  std::list<Updatable*>::iterator updateIt = this->updatables.begin();
  bool done = false;

  while (updateIt != this->updatables.end()) {
    if ((done = (*updateIt)->notify(notis))) {
      delete (*updateIt);
      updateIt = this->updatables.erase(updateIt);
    } else
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

void Game::start(int playerID, WaitingQueue<Notification*>& notif) {
  std::map<int, Player*>::iterator it = this->players.find(playerID);

  if (it != this->players.end()) {
    if (it->second->hasAdmin()) {
      started = true;
      EndMatch* endTimer = new EndMatch(yamlConfigReader.getMatchLength());
      this->updatables.push_back(endTimer);
      notif.push(new StartingMatch());
    }
  }
}

bool Game::hasStarted() { return started; }

ScoreBoard* Game::generateScoreboard(std::vector<Player*>& playersvect){

  std::sort(playersvect.begin(), playersvect.end(),
            [](Player* a, Player* b) -> bool {
              return a->getScore() >= b->getScore();
            });

  std::vector<uint32_t> scores;
  std::vector<uint32_t> ids;
  for (auto p : playersvect) {
    scores.push_back(p->getScore());
    ids.push_back(p->ID());
  }

  return new ScoreBoard(playersvect.size(), ids, scores);
}

ScoreBoard* Game::generateKillScoreboard(std::vector<Player*>& playersvect){
  std::sort(playersvect.begin(), playersvect.end(),
            [](Player* a, Player* b) -> bool {
              return a->getKills() >= b->getKills();
            });

  std::vector<uint32_t> kills;
  std::vector<uint32_t> ids;
  for (auto p : playersvect) {
    kills.push_back(p->getKills());
    ids.push_back(p->ID());
  }

  return new ScoreBoard(playersvect.size(), ids, kills);
}

// Averiguar si se puede pasar a un solo metodo que reciba un lambda con el sorting requerido.
ScoreBoard* Game::generateShotsFiredScoreBoard(std::vector<Player*>& playersvect){
  std::vector<uint32_t> shotsFired;
  std::vector<uint32_t> ids;

  std::sort(playersvect.begin(), playersvect.end(),
            [](Player* a, Player* b) -> bool {
              return a->getShotsFired() >= b->getShotsFired();
            });
  for (auto p : playersvect) {
    shotsFired.push_back(p->getShotsFired());
    ids.push_back(p->ID());
  }

  return new ScoreBoard(playersvect.size(), ids, shotsFired);
}

void Game::end(WaitingQueue<Notification*>& queue) {
  started = false;
  std::map<int, Player*>::iterator it = this->players.begin();

  std::vector<Player*> playersvect;
  for (; it != this->players.end(); ++it) {
    playersvect.push_back(it->second);
  }

  EndMatchNotif* endmatch = new EndMatchNotif(generateScoreboard(playersvect), generateKillScoreboard(playersvect), generateShotsFiredScoreBoard(playersvect));
  queue.push(endmatch);
}

Game::~Game() {
  std::map<int, Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    delete it->second;
  }

  std::list<Updatable*>::iterator it2 = this->updatables.begin();

  for (; it2 != this->updatables.end(); ++it2) {
    delete (*it2);
  }

  delete this->map;
}
