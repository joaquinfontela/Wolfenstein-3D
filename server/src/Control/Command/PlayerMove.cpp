#include "../../../includes/Control/Command/PlayerMove.h"

#include <list>

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/PlayerUpdatePosition.h"

PlayerMove::PlayerMove(int ID, int x, int y) {
  this->playerID = ID;
  this->x = x;
  this->y = y;
}

void PlayerMove::execute(NullPtrQueue<Notification*>& notifications) {
  PlayerUpdatePosition* noti =
      new PlayerUpdatePosition(this->playerID, this->x, this->y);
  notifications.push(noti);
}
