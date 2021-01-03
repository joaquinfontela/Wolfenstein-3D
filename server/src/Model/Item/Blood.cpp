#include "../../../includes/Model/Item/Blood.h"


Blood::Blood(int id) : Item(id){}

bool Blood::canBePickedUpBy(Player* p){
  return p->getHealth() < 11;
}

void Blood::pickUp(Player* p){

  p->addHealth(1);
}
