#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(unsigned int newAmmo) : Shootable(newAmmo), ID(5) {}
  ~MachineGun();
  unsigned int attack();
  int getID();

private:
  int ID;
};
