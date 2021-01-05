#ifndef DOOR_FACTORY_H
#define DOOR_FACTORY_H

#include "./Door.h"
#include "./LockableDoor.h"
#include "./UnlockableDoor.h"

class DoorFactory {
 public:
  Door* getDoor(int doorId);
};

#endif