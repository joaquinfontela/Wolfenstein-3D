#include "Weapon.h"

class Minigun : public Weapon {
 public:
  Minigun(int newAmmo);
  ~Minigun();
  unsigned int shoot();
};