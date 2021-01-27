#include "../../../includes/Model/Door/UnlockableDoor.h"

UnlockableDoor::UnlockableDoor() : Door() {locked = true; opening = false;}

bool UnlockableDoor::isLocked() { return locked; }

void UnlockableDoor::changeStatus(){
  if(locked){
    locked = false;
    opening = false;
  }else{
    locked = true;
  }

}

bool UnlockableDoor::unlock(bool hasKey){

  if(opening)
    return false;

  if(!locked)
    return false;

  opening = true;
  return true;
}

bool UnlockableDoor::lock(){
  locked = true;
  return true;
}
