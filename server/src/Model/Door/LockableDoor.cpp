#include "../../../includes/Model/Door/LockableDoor.h"

LockableDoor::LockableDoor() : Door() { locked = true; }

bool LockableDoor::isLocked() { return locked; }

bool LockableDoor::unlock(bool hasKey) {
  if (hasKey && locked){
      locked = false;
      return true;
  }

  return false;
}

bool LockableDoor::lock(){
  locked = true;

  return true;
}
