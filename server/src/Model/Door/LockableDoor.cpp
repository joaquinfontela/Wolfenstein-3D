#include "../../../includes/Model/Door/LockableDoor.h"

LockableDoor::LockableDoor() : Door() { locked = true; }

bool LockableDoor::isLocked() { return locked; }

bool LockableDoor::unlock(bool hasKey) {
  if (hasKey && locked){
      locked = false;
      return true;
  }else if(!locked){
      locked = true;
      return true;
  }

  return false;
}
