#include "../../../includes/Control/Notification/PlayerDropItem.h"
#include "../../../../common/includes/Socket/SocketWrapper.h"

#include "../../../../common/includes/protocol.h"

PlayerDropItem::PlayerDropItem(int x, int y, int itemID, int uniqueId) {
  this->x = x;
  this->y = y;
  this->itemID = itemID;
  this->uniqueId = uniqueId;
}

void PlayerDropItem::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_DROP_ITEM;

  socket.send(&opcode, sizeof(opcode));

  socket.send((uint32_t*)(&this->x), sizeof(this->x));
  socket.send((uint32_t*)(&this->y), sizeof(this->y));
  socket.send((uint32_t*)(&this->itemID), sizeof(this->itemID));
  socket.send((uint32_t*)(&this->uniqueId), sizeof(this->uniqueId));

}
