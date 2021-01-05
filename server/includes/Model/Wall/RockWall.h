#include "./Wall.h"

class RockWall : public Wall {
 public:
  RockWall(bool isTrueWall) : Wall(isTrueWall) {}
};