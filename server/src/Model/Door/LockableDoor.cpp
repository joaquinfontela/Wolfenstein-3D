#include "../../../includes/Model/Door/LockableDoor.h"
#include <iostream>

LockableDoor::LockableDoor() : Door() {
  locked = true;
  previouslyUnlocked = false;
 }

bool LockableDoor::isLocked() { return locked; }

bool LockableDoor::unlock(bool hasKey) {

  if(locked && previouslyUnlocked){
    locked = false;
    return true;
  }

  else if (hasKey && locked){
      locked = false;
      previouslyUnlocked = true;
      return true;
  }

  return false;
}

bool LockableDoor::lock(){
  locked = true;

  return true;
}
