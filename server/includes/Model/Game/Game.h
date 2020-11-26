#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>

#include "../Player/Player.h"

class Game {
 private:
  std::map<int, Player> players;

  // Considerar crear una clase Map que pueda manejar la logica de las
  // colisiones y que sepa su propio ID de mapa.
  int map[10][10];

 public:
  Game(std::string& mapFile, std::string& configFile);
  void addPlayer(int playerID);

  void start();

  void end();
};

#endif