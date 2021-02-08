#ifndef DOOR_FACTORY_H
#define DOOR_FACTORY_H

#include "./Door.h"
#include "./LockableDoor.h"
#include "./UnlockableDoor.h"

class DoorFactory {
 public:
  /*
   * @brief [SERVER-SIDE] Receives a doorId and returns the corresponding door.
   *
   * @param doorId integer that represents a door type.
   *
   * @return a dynamic pointer to a door if the id is valid, nullptr otherwise.
   */
  Door* getDoor(int doorId);
};

#endif