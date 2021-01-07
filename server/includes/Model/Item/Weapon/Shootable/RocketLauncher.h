#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(unsigned int newAmmo, unsigned int minDamagePerBullet,
                 unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                 unsigned int ammoLostPerShot)
      : Shootable(newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot),
        ID(1) {}
  ~RocketLauncher();
  unsigned int attack();
  bool hasAmmo();
  int getID();

 private:
  int ID;
};
