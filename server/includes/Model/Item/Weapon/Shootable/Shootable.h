#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  unsigned int ammo;
  virtual unsigned int shoot() = 0;

 public:
  Shootable(int newAmmo);
  virtual ~Shootable() = 0;
  unsigned int attack();
  bool outOfAmmo();
};