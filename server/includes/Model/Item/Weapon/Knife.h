#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "Weapon.h"

class Knife : public Weapon {
 public:
  Knife(unsigned int minDamagePerBullet, unsigned maxDamagePerBullet)
      : Weapon(minDamagePerBullet, maxDamagePerBullet), ID(0) {}
  ~Knife();
  int getID();
  unsigned int attack();
  bool hasAmmo();

 private:
  int ID;
};

#endif
