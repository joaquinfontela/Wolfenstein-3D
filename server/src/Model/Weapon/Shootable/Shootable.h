#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  int ammo;
  virtual void shoot() = 0;

 public:
  Shootable(int newAmmo);
  void attack();
  bool outOfAmmo();
};