#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "hud.h"
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

typedef struct Door {
  int mapX, mapY;
  bool hit;
  double perpWallDist;
  int side;
  void operator()(int mapX, int mapY, int side) {
    this->mapX = mapX;
    this->mapY = mapY;
    this->side = side;
    this->hit  = true;
  }
  void calcDistToWall(int posX, int posY, int stepX, int stepY, int rayDirX, int rayDirY) {
    if(this->side == 0){
      perpWallDist = (mapX - posX + (1 - stepX) / 2) / (rayDirX + 0.001);
    }
    else{
      perpWallDist = (mapY - posY + (1 - stepY) / 2) / (rayDirY + 0.001);
    }

    std::cout<<"Wall Dist: "<<perpWallDist<<std::endl;

  }
} Door;

class Raycaster {
 public:
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b, SdlWindow* window,
            Player* player, std::vector<Drawable*>& sprites, std::mutex& lock, Hud& hud) :
            alive(b), manager(manager) , matrix(m) , player(player) ,
            window(window), sprites(sprites) , lock(lock) , hud(hud) {
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
