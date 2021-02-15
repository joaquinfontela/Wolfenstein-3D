#ifndef LUARAYCASTER_H_
#define LUARAYCASTER_H_

#include <math.h>

#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>

#include "../../../common/includes/Map/Map.h"
#include "../includes/clientprotocol.h"
#include "../includes/player.h"
#include "GameState.h"

namespace Lua {

class Raycaster {
 public:
  Raycaster(Map& m, std::atomic<bool>& b, int width, int height, Player* player,
            std::vector<Drawable*>& sprites, std::mutex& lock,
            Lua::GameState& gameState, double* distanceBuffer)
      : matrix(m),
        alive(b),
        width(width),
        height(height),
        player(player),
        sprites(sprites),
        lock(lock),
        gameState(gameState) {
    this->distanceBuffer = distanceBuffer;
  }
  void run();

 private:
  Map& matrix;
  Lua::GameState& gameState;
  std::atomic<bool>& alive;
  double* distanceBuffer;
  int width, height;
  Player* player;
  std::vector<Drawable*>& sprites;
  std::mutex& lock;
  double dirX, dirY, x, y, planeX, planeY;
  void getPlayerData();
};

}  // namespace Lua

#endif  // LUARAYCASTER_H_
