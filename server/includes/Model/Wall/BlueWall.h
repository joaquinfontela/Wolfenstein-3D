#ifndef BLUE_WALL_H
#define BLUE_WALL_H

#include "./Wall.h"

class BlueWall : public Wall {
 public:
  BlueWall(bool isTrueWall) : Wall(isTrueWall) {}
};

#endif