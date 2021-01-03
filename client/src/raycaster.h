#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "hud.h"
#include "player.h"
#include "sdlwindow.h"
#include "texturemanager.h"
#include "../../common/includes/Map/Map.h"

#include <mutex>
#include <atomic>
#include <vector>
#include <math.h>

#define PI 3.14159265359

class Raycaster {
 public:
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b, SdlWindow* window, Player* player, std::vector<Drawable*>& sprites, std::mutex& lock, Hud& hud) :
          alive(b), manager(manager) , matrix(m) , player(player) , window(window), sprites(sprites) , lock(lock) , hud(hud) {
    manager.getWindowSize(&this->width, &this->height);
    this->distanceToProyection = floor((width/2)/(tan((PI/2) - PI/3)));
  }
  void run();
 private:
  std::atomic<bool>& alive;
  TextureManager& manager;
  Map& matrix;
  Player* player;
  SdlWindow* window;
  std::vector<Drawable*>& sprites;
  std::mutex& lock;
  Hud& hud;
  int width;
  int height;

  double distanceToProyection;
};

#endif  // RAYCASTER_H_
