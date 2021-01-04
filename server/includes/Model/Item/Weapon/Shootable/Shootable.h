#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  unsigned int ammo;
  unsigned int shoot();

 public:
  Shootable(int newAmmo);
  virtual ~Shootable() = 0;
  bool outOfAmmo();
};