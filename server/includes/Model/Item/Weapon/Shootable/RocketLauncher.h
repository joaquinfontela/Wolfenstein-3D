#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(unsigned int uniqueId, unsigned int newAmmo,
                 unsigned int minDamagePerBullet, unsigned maxDamagePerBullet,
                 unsigned int shotsPerBlast, unsigned int ammoLostPerShot)
      : Shootable(uniqueId, newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot),
        ID(5) {}
  ~RocketLauncher();
  bool hasAmmo();
  int getUniqueId();
  int getID();
  int getRange();

 private:
  int ID;
};
