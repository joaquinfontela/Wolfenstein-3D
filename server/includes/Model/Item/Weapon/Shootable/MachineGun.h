#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(unsigned int newAmmo) : Shootable(newAmmo), ID(3) {}
  ~MachineGun();
  unsigned int attack();
  int getID();
  bool hasAmmo();

private:
  int ID;
};
