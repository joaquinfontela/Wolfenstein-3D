#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(unsigned int newAmmo, unsigned int minDamagePerBullet,
          unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
          unsigned int ammoLostPerShot, unsigned int precision,
          unsigned int blastFrequency)
      : Shootable(newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision, blastFrequency),
        ID(3) {}
  ~Minigun();
  unsigned int attack();
  int getID();
  bool hasAmmo();

 private:
  int ID;
};
