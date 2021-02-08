#ifndef WALL_FACTORY_H
#define WALL_FACTORY_H

#include "./BlueWall.h"
#include "./GreyStoneWall.h"
#include "./RockWall.h"
#include "./Wall.h"
#include "./WoodenWall.h"

class WallFactory {
 public:
  /*
   * @brief [SERVER-SIDE] Receives a wallId and returns the corresponding wall.
   *
   * @param wallId integer that represents a wall type.
   *
   * @return a dynamic pointer to a wall if the id is valid, nullptr otherwise.
   */
  Wall* getWall(int wallId);
};

#endif