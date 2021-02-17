#include "../../../includes/Control/Notification/PlayerDropItem.h"

#include "../../../../common/includes/protocol.h"

PlayerDropItem::PlayerDropItem(double x, double y, int itemID, int uniqueId) {
  this->x = x;
  this->y = y;
  this->itemID = itemID;
  this->uniqueId = uniqueId;
}

void PlayerDropItem::send(SocketWrapper& socket) {
  uint32_t opcode = PLAYER_DROP_ITEM;

  socket.send(opcode);
  socket.send(this->x);
  socket.send(this->y);
  socket.send(uint32_t(this->itemID));
  socket.send(uint32_t(this->uniqueId));

}
