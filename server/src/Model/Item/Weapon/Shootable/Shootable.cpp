#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(unsigned int uniqueId, int newAmmo,
                     unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot)
    : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = NULL;
  this->blastFrequency = NULL;
}

Shootable::Shootable(unsigned int uniqueId, int newAmmo,
                     unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot, unsigned int precision)
    : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = precision;
  this->blastFrequency = NULL;
}

Shootable::Shootable(unsigned int uniqueId, int newAmmo,
                     unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot, unsigned int precision,
                     unsigned int blastFrequency)
    : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = precision;
  this->blastFrequency = blastFrequency;
}

Shootable::~Shootable() {}

unsigned int Shootable::attack(int& ammo) {
  int i;
  unsigned int damage = 0;
  for (i = 0; i < this->shotsPerBlast; i++) {
    if(ammo >= this->ammoLostPerShot){
      damage += this->shoot();
      ammo -= this->ammoLostPerShot;
    }

  }
  return damage;
}

unsigned int Shootable::shoot() {
  return this->getRandomDamage();
}

// bool Shootable::outOfAmmo() { return (ammo == 0); }
