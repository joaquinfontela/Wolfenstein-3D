#ifndef __WEAPON_H__
#define __WEAPON_H__


class Weapon{

protected:

  unsigned int ammo;
  // faltan cosas como el fire rate, precision y los datos particulares que hagan falta.

public:

  Weapon(){}
  Weapon(unsigned int ammo) : ammo(ammo){}

  // Devuelve el daño que haria un ataque.
  virtual unsigned int attack() = 0;
  ~Weapon(){}

};



#endif
