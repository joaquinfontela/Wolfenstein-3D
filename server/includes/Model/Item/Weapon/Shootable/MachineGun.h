#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(unsigned int newAmmo, unsigned int minDamagePerBullet,
             unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
             unsigned int ammoLostPerShot, unsigned int precision,
             unsigned int blastFrequency)
      : Shootable(newAmmo, minDamagePerBullet, maxDamagePerBullet,
                  shotsPerBlast, ammoLostPerShot, precision, blastFrequency),
        ID(4) {}
  ~MachineGun();
  int getID();
  bool hasAmmo();

 private:
  int ID;
};
