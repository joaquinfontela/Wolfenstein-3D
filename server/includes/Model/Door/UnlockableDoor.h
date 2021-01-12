#include "./Door.h"
#include "../Player/Player.h"

class UnlockableDoor : public Door {
 public:
  UnlockableDoor();
  bool isLocked();
  bool unlock(Player* p);

private:
  bool locked;
};
