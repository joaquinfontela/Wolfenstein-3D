#include "../../../includes/Model/Door/LockableDoor.h"

LockableDoor::LockableDoor() : Door() { locked = true; }

bool LockableDoor::isLocked() { return locked; }

bool LockableDoor::unlock(bool hasKey) {
  if (hasKey){
      locked = false;
      return true;
  }

  return false;
}
