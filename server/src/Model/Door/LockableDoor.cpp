#include "../../../includes/Model/Door/LockableDoor.h"

LockableDoor::LockableDoor() : Door() { locked = true; }

bool LockableDoor::isLocked() { return locked; }

void LockableDoor::unlock(Key* key) {
  if (key != nullptr) locked = false;
}