#ifndef __UNLOCKABLE_DOOR_H__
#define __UNLOCKABLE_DOOR_H__

#include "./Door.h"




class UnlockableDoor : public Door {
 public:
  UnlockableDoor();
  bool isLocked();
  bool unlock(bool hasKey);
  bool lock();
  void changeStatus();

private:
  bool locked;
  bool opening;
};


#endif
