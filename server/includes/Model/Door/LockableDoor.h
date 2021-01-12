#include "../Player/Player.h"
#include "./Door.h"

class LockableDoor : public Door {
 private:
  bool locked;

 public:
  LockableDoor();
  bool isLocked();
  bool unlock(Player* p);
};
