#ifndef SHOOTABLE_H
#define SHOOTABLE_H

#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  unsigned int ammo;
  unsigned int blastFrequency;
  unsigned int shotsPerBlast;
  unsigned int ammoLostPerShot;
  unsigned int precision;
  unsigned int shoot();

 public:
  Shootable(int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot);
  Shootable(int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot, unsigned int precision);
  Shootable(int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot, unsigned int precision,
            unsigned int blastFrequency);
  ~Shootable();
  virtual bool hasAmmo() = 0;
  unsigned int attack();
  // bool outOfAmmo();
};

#endif
