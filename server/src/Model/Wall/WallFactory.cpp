#include "../../../includes/Model/Wall/WallFactory.h"

Wall* WallFactory::getWall(int wallId) {
  switch (wallId) {
    case 301:
      return new BlueWall(true);
      break;

    case 302:
      return new GreyStoneWall(true);
      break;

    case 303:
      return new RockWall(true);
      break;

    case 304:
      return new WoodenWall(true);
      break;

    case 351:
      return new BlueWall(false);
      break;

    case 352:
      return new GreyStoneWall(false);
      break;

    case 353:
      return new RockWall(false);
      break;

    case 354:
      return new WoodenWall(false);
      break;

    default:
      return nullptr;
      break;
  }
}