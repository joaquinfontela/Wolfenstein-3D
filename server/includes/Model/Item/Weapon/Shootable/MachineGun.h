#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(unsigned int uniqueId, unsigned int newAmmo,
             unsigned int minDamagePerBullet, unsigned maxDamagePerBullet,
             unsigned int shotsPerBlast, unsigned int ammoLostPerShot,
             unsigned int precision, unsigned int blastFrequency)
      : Shootable(uniqueId, newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision, blastFrequency),
        ID(3) {}
  ~MachineGun();
  int getID();
  int getUniqueId();
  bool hasAmmo();
  int getRange();

 private:
  int ID;
};
