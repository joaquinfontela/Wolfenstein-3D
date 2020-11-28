#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  int ammo;
  virtual void shoot() = 0;

 public:
  Shootable(int newAmmo);
  virtual ~Shootable() = 0;
  void attack();
  bool outOfAmmo();
};