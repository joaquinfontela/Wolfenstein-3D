#include "../../../includes/Model/Door/DoorFactory.h"
#include <iostream>

Door* DoorFactory::getDoor(int doorId) {
  switch (doorId) {
    case 201:
      return new UnlockableDoor();
      break;

    case 202:
      std::cout<<"Adding a Lockable door."<<std::endl;
      return new LockableDoor();
      break;

    default:
      return nullptr;
      break;
  }
}
