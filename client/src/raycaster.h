#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "player.h"
#include "sdlwindow.h"
#include "texturemanager.h"
#include "../../common/includes/Map/Map.h"

#include <atomic>
#include <vector>
#include <math.h>

#define PI 3.14159265359

class Raycaster {
 public:
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b, SdlWindow* window, Player* player, std::vector<Drawable*>& sprites) :
          alive(b), manager(manager) , matrix(m) , player(player) , window(window), sprites(sprites) {
    manager.getWindowSize(&this->width, &this->height);
    this->distanceToProyection = floor((width/2)/(tan((PI/2) - PI/3)));
  }
  void run();
 private:
  std::vector<Drawable*>& sprites;
  std::atomic<bool>& alive;
  int width;
  int height;
  TextureManager& manager;
  Map& matrix;
  double distanceToProyection;
  Player* player;
  SdlWindow* window;
};

#endif  // RAYCASTER_H_
