#ifndef __ITEM_H__
#define __ITEM_H__

#include "../Player/Player.h"
class Player;

class Item {
 protected:
  int id;
  int itemID;

 public:
  Item() {}
  Item(int itemID, int id) : id(id), itemID(itemID) {}
  int getID() { return id; }
  int getItemID() { return itemID; }

  /*
   * @param p a pointer to a player.
   *
   * @return a boolean determining if this item can be picked up by p.
   */
  virtual bool canBePickedUpBy(Player* p) = 0;

  /*
   * @brief [SERVER-SIDE] Player p picks up this item.
   *
   * @param p a pointer to a player.
   */
  virtual void pickUp(Player* p) = 0;
  ~Item() {}
};

#endif
