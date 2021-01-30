#ifndef LUARAYCASTER_H_
#define LUARAYCASTER_H_

#include "../player.h"
#include "../clientprotocol.h"
#include "../../../common/includes/Map/Map.h"

#include <mutex>
#include <atomic>
#include <vector>
#include <math.h>
#include <iostream>

namespace Lua {

  class Raycaster {
   public:
    Raycaster(Map& m, std::atomic<bool>& b, int width, int height, Player* player,
              std::vector<Drawable*>& sprites, std::mutex& lock) : matrix(m), alive(b),
              width(width), height(height), player(player), sprites(sprites), lock(lock) {}
    void run();
   private:
    Map& matrix;
    std::atomic<bool>& alive;
    int width, height;
    Player* player;
    std::vector<Drawable*>& sprites;
    std::mutex& lock;
  };

}

#endif  // LUARAYCASTER_H_
