#include "../../../includes/Model/Door/UnlockableDoor.h"

UnlockableDoor::UnlockableDoor() : Door() {locked = true;}

bool UnlockableDoor::isLocked() { return locked; }

bool UnlockableDoor::unlock(bool hasKey){

  if(locked)
    locked = false;
  else
    return false;

  return true;
}

bool UnlockableDoor::lock(){
  locked = true;
  return true;
}
