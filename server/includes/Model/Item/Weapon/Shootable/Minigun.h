#include "Shootable.h"
#include <iostream>

class Minigun : public Shootable {
 public:
  Minigun(unsigned int uniqueId, unsigned int newAmmo,
          unsigned int minDamagePerBullet, unsigned maxDamagePerBullet,
          unsigned int shotsPerBlast, unsigned int ammoLostPerShot,
          unsigned int precision, float blastFrequency)
      : Shootable(uniqueId, newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision, blastFrequency),
        ID(4) {}
  ~Minigun();
  int getID();
  int getUniqueId();
  bool hasAmmo();
  int getRange();

 private:
  int ID;
};
