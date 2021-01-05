#include "./Door.h"

class UnlockableDoor : public Door {
 public:
  UnlockableDoor();
  bool isLocked();
};