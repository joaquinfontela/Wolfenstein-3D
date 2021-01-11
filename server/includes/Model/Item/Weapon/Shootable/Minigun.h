#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(unsigned int uniqueId, unsigned int newAmmo,
          unsigned int minDamagePerBullet, unsigned maxDamagePerBullet,
          unsigned int shotsPerBlast, unsigned int ammoLostPerShot,
          unsigned int precision, unsigned int blastFrequency)
      : Shootable(uniqueId, newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision, blastFrequency),
        ID(4) {}
  ~Minigun();
  int getID();
  bool hasAmmo();
  int getRange();

 private:
  int ID;
};
