#include "../../../includes/Model/Door/UnlockableDoor.h"

UnlockableDoor::UnlockableDoor() : Door() {locked = true;}

bool UnlockableDoor::isLocked() { return locked; }

bool UnlockableDoor::unlock(bool hasKey){
  locked = false;
  return true;
}
