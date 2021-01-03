#ifndef __KIT_H__
#define __KIT_H__

#include "Item.h"


class Kit : public Item{
public:

  Kit(int id);

  bool canBePickedUpBy(Player* p);
  void pickUp(Player* p);

};

#endif
