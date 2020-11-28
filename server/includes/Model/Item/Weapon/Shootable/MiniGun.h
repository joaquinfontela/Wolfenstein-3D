#include "Shootable.h"

class MiniGun : public Shootable {
 public:
  MiniGun(int newAmmo);
  ~MiniGun();
  void shoot();
};