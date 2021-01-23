#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"
#include <iostream>

Shootable::Shootable(unsigned int uniqueId, int newAmmo,
                     unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot)
    : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = 0;
  this->blastFrequency = 0;
  this->timeSinceLastShot = 0;
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
  this->blastFrequency = 0;
  this->timeSinceLastShot = 0;
}

Shootable::Shootable(unsigned int uniqueId, int newAmmo,
                     unsigned int minDamagePerBullet,
                     unsigned maxDamagePerBullet, unsigned int shotsPerBlast,
                     unsigned int ammoLostPerShot, unsigned int precision,
                     float blastFrequency)
    : Weapon(uniqueId, minDamagePerBullet, maxDamagePerBullet) {
  this->ammo = newAmmo;
  this->shotsPerBlast = shotsPerBlast;
  this->ammoLostPerShot = ammoLostPerShot;
  this->precision = precision;
  this->blastFrequency = blastFrequency;
  this->timeSinceLastShot = 0;
}

Shootable::~Shootable() {}

unsigned int Shootable::attack(int& ammo, float timeElapsed) {
  int i;
  unsigned int damage = 0;

  if(timeSinceLastShot + timeElapsed > this->blastFrequency){
    for (i = 0; i < this->shotsPerBlast; i++) {
      if(ammo >= this->ammoLostPerShot){
        damage += this->shoot();
        ammo -= this->ammoLostPerShot;
      }
      else{
        damage = -1;
        break;
      }
    }
    timeSinceLastShot = 0;
  }else{
    timeSinceLastShot += timeElapsed;
    return -1;
  }

  return damage;
}

unsigned int Shootable::shoot() {
  return this->getRandomDamage();
}

// bool Shootable::outOfAmmo() { return (ammo == 0); }
