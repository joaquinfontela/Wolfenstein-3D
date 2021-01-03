#include "../../../includes/Model/Item/Key.h"



Key::Key(int id) : Item(id){}

bool Key::canBePickedUpBy(Player* p){
  return true;
}

void Key::pickUp(Player* p){
  p->pickupKey();
}
