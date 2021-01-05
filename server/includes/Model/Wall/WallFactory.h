#ifndef WALL_FACTORY_H
#define WALL_FACTORY_H

#include "./BlueWall.h"
#include "./GreyStoneWall.h"
#include "./RockWall.h"
#include "./Wall.h"
#include "./WoodenWall.h"

class WallFactory {
 public:
  Wall* getWall(int wallId);
};

#endif