#ifndef __LOCKABLE_DOOR_H__
#define __LOCKABLE_DOOR_H__
#include "./Door.h"

class LockableDoor : public Door {
 private:
  bool locked;
  bool previouslyUnlocked;
  bool opening;

 public:
  LockableDoor();
  bool isLocked();
  bool unlock(bool hasKey);
  bool lock();
  void changeStatus();
};

#endif
