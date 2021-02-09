#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <cstdlib>

class Weapon {
 private:
  unsigned int minDamagePerBullet;
  unsigned int maxDamagePerBullet;

 protected:

  unsigned int uniqueId;

  /*
   * @return a random value between minDamagePerBullet and maxDamagePerBullet.
   */
  unsigned int getRandomDamage();

 public:
  Weapon(unsigned int uniqueId, unsigned int minDamagePerBullet,
         int maxDamagePerBullet);
  Weapon(unsigned int ammo) {}

  /*
   * @return the id of the weapon type.
   */
  virtual int getID() = 0;

  /*
   * @return the unique id of the weapon.
   */
  virtual int getUniqueId() = 0;

  /*
   * @return true if the weapon has ammo left, false otherwise.
   */
  virtual bool hasAmmo() = 0;

  /*
   * @return the range of the weapon.
   */
  virtual int getRange() = 0;

  /*
   * @brief [SERVER-SIDE] Recieves the ammo left and time elapsed since last
   * shot attempt, and returns the damage caused by the attack.
   *
   * @param ammo reference to an integer that represents the ammo left.
   *
   * @param timeElapsed time elapsed since last shot attempt.
   *
   * @return damage caused by the attack, or -1 if the attack failed.
   */
  virtual unsigned int attack(int& ammo, float timeElapsed) = 0;
  ~Weapon() {}
};

#endif
