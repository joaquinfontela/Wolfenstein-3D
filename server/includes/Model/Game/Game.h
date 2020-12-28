#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>

#include "../Player/Player.h"
#include "../../../../common/includes/Map/Map.h"

class Game {
 private:
  std::map<int, Player*> players;
  Map map;

  // Deberia tener una estructura que maneje los datos del configFile de YAML

 public:
  Game(std::string mapFile, std::string configFile);
  void addPlayer(int playerID);
  void removePlayer(int playerID);

  void updatePlayerMoveSpeed(int playerID, double moveSpeed);
  void updatePlayerRotationSpeed(int playerID, double rotSpeed);
  void start();
  void end();
};

#endif
