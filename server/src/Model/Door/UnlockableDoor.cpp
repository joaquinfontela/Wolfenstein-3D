#include "../../../includes/Model/Door/UnlockableDoor.h"

UnlockableDoor::UnlockableDoor() : Door() {locked = true;}

bool UnlockableDoor::isLocked() { return locked; }

bool UnlockableDoor::unlock(Player* p){
  locked = false;
  return true;
}
