#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(unsigned int newAmmo) : Shootable(newAmmo), ID(4) {}
  ~Minigun();
  unsigned int attack();
  int getID();

private:
  int ID;
};
