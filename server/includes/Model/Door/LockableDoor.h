#include "../Item/Key.h"
#include "./Door.h"

class LockableDoor : public Door {
 private:
  bool locked;

 public:
  LockableDoor();
  bool isLocked();
  void unlock(Key* key);
};