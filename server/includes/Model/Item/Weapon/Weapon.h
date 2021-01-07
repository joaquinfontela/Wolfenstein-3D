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
  unsigned int getRandomDamage();

 public:
  Weapon(unsigned int minDamagePerBullet, int maxDamagePerBullet);
  Weapon(unsigned int ammo) {}
  virtual int getID() = 0;
  virtual bool hasAmmo() = 0;

  // Devuelve el daño que haria un ataque.
  virtual unsigned int attack() = 0;
  ~Weapon() {}
};

#endif
