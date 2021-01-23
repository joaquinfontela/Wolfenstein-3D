#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <cstdlib>

class Weapon {
 private:
  unsigned int minDamagePerBullet;
  unsigned int maxDamagePerBullet;

 protected:
  // faltan cosas como el fire rate, precision y los datos particulares que
  // hagan falta.
  unsigned int uniqueId;
  unsigned int getRandomDamage();

 public:
  Weapon(unsigned int uniqueId, unsigned int minDamagePerBullet,
         int maxDamagePerBullet);
  Weapon(unsigned int ammo) {}
  virtual int getID() = 0;
  virtual int getUniqueId() = 0;
  virtual bool hasAmmo() = 0;
  virtual int getRange() = 0;

  // Devuelve el daño que haria un ataque.
  virtual unsigned int attack(int& ammo, float timeElapsed) = 0;
  ~Weapon() {}
};

#endif
