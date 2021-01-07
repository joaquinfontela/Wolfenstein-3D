#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo, unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot)
    : Weapon(minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = NULL;
  this->blastFrequency = NULL;
}

Shootable::Shootable(int newAmmo, unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot, unsigned int precision)
    : Weapon(minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = precision;
  this->blastFrequency = NULL;
}

Shootable::Shootable(int newAmmo, unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot, unsigned int precision,
                     unsigned int blastFrequency)
    : Weapon(minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = precision;
  this->blastFrequency = blastFrequency;
}

Shootable::~Shootable() {}

unsigned int Shootable::shoot() {
  ammo--;
  return this->getRandomDamage();
}

// bool Shootable::outOfAmmo() { return (ammo == 0); }
