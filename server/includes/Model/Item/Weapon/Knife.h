#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "Weapon.h"

class Knife : public Weapon {
 public:
  Knife(unsigned int uniqueId, unsigned int minDamagePerBullet,
        unsigned maxDamagePerBullet)
      : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet), ID(1) {}
  ~Knife();
  int getID();
  int getUniqueId();
  unsigned int attack(int& ammo, float timeElapsed);
  bool hasAmmo();
  int getRange();

 private:
  int ID;
};

#endif
