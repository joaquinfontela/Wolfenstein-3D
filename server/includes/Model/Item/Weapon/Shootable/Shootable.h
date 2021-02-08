#ifndef SHOOTABLE_H
#define SHOOTABLE_H

#include <climits>

#include "../Weapon.h"

class Shootable : public Weapon {
 protected:
  unsigned int ammo;
  float blastFrequency;
  unsigned int shotsPerBlast;
  unsigned int ammoLostPerShot;
  unsigned int precision;

  /*
   * @brief [SERVER-SIDE] Simulates a shot of a bullet.
   *
   * @return the damage of a single shot.
   */
  unsigned int shoot();
  float timeSinceLastShot;

 public:
  Shootable(unsigned int uniqueId, int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot);
  Shootable(unsigned int uniqueId, int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot, unsigned int precision);
  Shootable(unsigned int uniqueId, int newAmmo, unsigned int minDamagePerBullet,
            unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
            unsigned int ammoLostPerShot, unsigned int precision,
            float blastFrequency);
  ~Shootable();
  virtual bool hasAmmo() = 0;
  unsigned int attack(int& ammo, float timeElapsed);
  // bool outOfAmmo();
};

#endif
