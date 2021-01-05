#include "../../../includes/Model/Door/DoorFactory.h"

Door* DoorFactory::getDoor(int doorId) {
  switch (doorId) {
    case 201:
      return new UnlockableDoor();
      break;

    case 202:
      return new LockableDoor();
      break;

    default:
      return nullptr;
      break;
  }
}