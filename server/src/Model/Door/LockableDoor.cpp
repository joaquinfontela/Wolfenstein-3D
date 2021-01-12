#include "../../../includes/Model/Door/LockableDoor.h"

LockableDoor::LockableDoor() : Door() { locked = true; }

bool LockableDoor::isLocked() { return locked; }

bool LockableDoor::unlock(Player* p) {
  if (p->hasKey()){
      locked = false;
      return true;
  }

  return false;
}
