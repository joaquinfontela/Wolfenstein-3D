#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Shootable.h"

class Pistol : public Shootable {
 public:
  Pistol(unsigned int uniqueId, unsigned int ammo,
         unsigned int minDamagePerBullet, unsigned maxDamagePerBullet,
         unsigned int shotsPerBlast, unsigned int ammoLostPerShot,
         unsigned int precision)
      : Shootable(uniqueId, ammo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision),
        ID(2) {}
  int getID();
  int getUniqueId();
  bool hasAmmo();
  int getRange();

 private:
  int ID;
};

#endif
