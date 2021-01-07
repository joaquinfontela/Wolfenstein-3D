#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Shootable.h"

class Pistol : public Shootable {
 public:
  Pistol(unsigned int ammo, unsigned int minDamagePerBullet,
         unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
         unsigned int ammoLostPerShot, unsigned int precision)
      : Shootable(ammo, minDamagePerBullet, maxDamagePerBullet, shotsPerBlast,
                  ammoLostPerShot, precision),
        ID(2) {}
  int getID();

  // Devuelve el daño que haria el disparo.
  unsigned int attack();
  bool hasAmmo();

 private:
  int ID;
};

#endif
