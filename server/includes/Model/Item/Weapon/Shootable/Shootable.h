#ifndef SHOOTABLE_H
#define SHOOTABLE_H

#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  unsigned int ammo;
  unsigned int shoot();

 public:
  Shootable(int newAmmo);
  ~Shootable();
  bool outOfAmmo();
};

#endif