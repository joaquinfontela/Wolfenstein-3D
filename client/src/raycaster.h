#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "hud.h"
#include "door.h"
#include "player.h"
#include "sdlwindow.h"
#include "texturemanager.h"
#include "clientprotocol.h"
#include "../../common/includes/Map/Map.h"

#include <mutex>
#include <atomic>
#include <vector>
#include <math.h>
#include <iostream>

#define MAX_NUMBER_OF_DOORS_PER_FRAME 10

class Raycaster {
 public:
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b, SdlWindow* window,
            Player* player, std::vector<Drawable*>& sprites, std::mutex& lock, Hud& hud) :
            alive(b), manager(manager), matrix(m), player(player),
            window(window), sprites(sprites), lock(lock), hud(hud) {
    manager.getWindowSize(&this->width, &this->height);
    this->doors.reserve(MAX_NUMBER_OF_DOORS_PER_FRAME);
  }
  bool hitDoor(const int& matrixXCoord, const int& matrixYCoord);
  void run();
 private:
  Area destArea;
  Area srcArea;
  std::atomic<bool>& alive;
  TextureManager& manager;
  Map& matrix;
  Player* player;
  SdlWindow* window;
  std::vector<Drawable*>& sprites;
  std::mutex& lock;
  Hud& hud;
  int width, height;
  std::vector<Door> doors;
};

#endif  // RAYCASTER_H_
