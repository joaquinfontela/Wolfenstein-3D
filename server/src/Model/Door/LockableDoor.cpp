#include "../../../includes/Model/Door/LockableDoor.h"
#include <iostream>

LockableDoor::LockableDoor() : Door() {
  locked = true;
  previouslyUnlocked = false;
  opening = false;
 }

bool LockableDoor::isLocked() { return locked; }

void LockableDoor::changeStatus(){
  if(locked){
    locked = false;
    opening = false;
  }else{
    locked = true;
  }
}

bool LockableDoor::unlock(bool hasKey) {

  if(locked && previouslyUnlocked){
    opening = true;
    return true;
  }

  else if (hasKey && locked){
    opening = true;
    previouslyUnlocked = true;
    return true;
  }

  return false;
}

bool LockableDoor::lock(){
  locked = true;

  return true;
}
