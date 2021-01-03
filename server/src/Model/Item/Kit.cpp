#include "../../../includes/Model/Item/Kit.h"


Kit::Kit(int id) : Item(id){}

bool Kit::canBePickedUpBy(Player* p){

  return !p->hasFullHealth();
}

void Kit::pickUp(Player* p){

  // Probablemente la vida deberia venir del configFile por lo que capaz deberia recibir la vida que quiero que sume por parametro del constructor.
  p->addHealth(20);
}
