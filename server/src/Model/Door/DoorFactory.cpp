#include "../../../includes/Model/Door/DoorFactory.h"
#include <iostream>

Door* DoorFactory::getDoor(int doorId) {
  switch (doorId) {
    case 202:
      return new UnlockableDoor();
      break;

    case 201:
      return new LockableDoor();
      break;

    default:
      return nullptr;
      break;
  }
}
