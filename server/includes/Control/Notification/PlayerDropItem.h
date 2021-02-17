#ifndef __PLAYER_DROP_ITEM_H__
#define __PLAYER_DROP_ITEM_H__

#include "Notification.h"

class PlayerDropItem : public Notification {
 private:
  double x, y;
  int itemID, uniqueId;

 public:
  PlayerDropItem(double x, double y, int itemId, int uniqueId);
  void send(SocketWrapper& socket);
};

#endif
