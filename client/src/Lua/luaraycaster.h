#ifndef LUARAYCASTER_H_
#define LUARAYCASTER_H_

#include "../player.h"
#include "../clientprotocol.h"
#include "../../../common/includes/Map/Map.h"
#include "GameState.h"
#include <mutex>
#include <atomic>
#include <vector>
#include <math.h>
#include <iostream>

namespace Lua {

  class Raycaster {
   public:
    Raycaster(Map& m, std::atomic<bool>& b, int width, int height, Player* player,
              std::vector<Drawable*>& sprites, std::mutex& lock, Lua::GameState& gameState, double* distanceBuffer) : matrix(m), alive(b),
              width(width), height(height), player(player), sprites(sprites), lock(lock), gameState(gameState) {
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
  };

}

#endif  // LUARAYCASTER_H_
