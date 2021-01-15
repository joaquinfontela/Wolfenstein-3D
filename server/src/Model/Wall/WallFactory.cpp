#include "../../../includes/Model/Wall/WallFactory.h"
#include <iostream>

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

    case 305:
      return new BlueWall(true);
      break;

    case 306:
      return new BlueWall(true);
      break;

    case 307:
      return new BlueWall(true);
      break;

    case 308:
      return new BlueWall(true);

    case 309:
      return new BlueWall(true);

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
